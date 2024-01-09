#include "../../include/managers/network_manager.hpp"

void NetworkManager::send_connection_response(bool is_accepted, std::uint32_t player_id)
{
    rtype::ConnectResponse response;

    if (is_accepted) {
        response.set_player_id(player_id);
        response.set_status(rtype::ConnectResponseStatus::SUCCESS);
    } else {
        response.set_status(rtype::ConnectResponseStatus::SERVER_FULL);
    }

    std::cout << "Sending connection response: " << response.DebugString() << std::endl;

    rtype::Payload payload;
    payload.mutable_connect_response()->CopyFrom(response);

    std::string serialized_response;
    payload.SerializeToString(&serialized_response);

    _socket.async_send_to(
        boost::asio::buffer(
            serialized_response, serialized_response.size() * sizeof(std::string::value_type)
        ),
        _remote_endpoint,
        [this](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
            handle_send(error);
        }
    );
}

void NetworkManager::handle_connection_request(const rtype::Connect& connect_message)
{
    if (_sessions.size() >= MAX_NUMBER_OF_PLAYERS) {
        std::cout << "Connection request rejected (Server Full): " << connect_message.player_name()
                  << std::endl;
        send_connection_response(false, 0);
        return;
    }

    std::cout << "Connection request from: " << connect_message.player_name() << std::endl;
    std::uint32_t player_id = _next_player_id++;

    entt::entity playerEntityId = static_cast<entt::entity>(player_id);
    entt::entity player = _entityManager.createPlayer(playerEntityId);

    auto session = std::make_shared<PlayerSession>(_remote_endpoint, player);
    _sessions[_remote_endpoint] = session;

    send_connection_response(true, player_id);
}

void NetworkManager::handle_player_quit(
    std::shared_ptr<PlayerSession>& session, entt::entity playerEntity
)
{
    std::cout << RED << "Player " << static_cast<uint32_t>(playerEntity) << " quit the game."
              << RESET << std::endl;

    _entityManager.getRegistry().destroy(playerEntity);
    _sessions.erase(session->endpoint());
}

// ! BROADCAST ->
void NetworkManager::addPlayerStateToGameState(
    rtype::GameState& game_state, entt::registry& registry
)
{
    // Add player states : 1 player/session
    for (const auto& [endpoint, session] : _sessions) {
        auto playerEntity = session->getPlayerEntity();

        if (registry.all_of<TransformComponent, HealthComponent, ScoreComponent>(playerEntity)) {
            auto& transformComponent = registry.get<TransformComponent>(playerEntity);
            auto& healthComponent = registry.get<HealthComponent>(playerEntity);
            auto& scoreComponent = registry.get<ScoreComponent>(playerEntity);

            rtype::PlayerState player_state;
            player_state.set_player_id(static_cast<uint32_t>(playerEntity));
            player_state.set_pos_x(transformComponent.x);
            player_state.set_pos_y(transformComponent.y);
            player_state.set_health(healthComponent.healthPoints);
            game_state.add_players()->CopyFrom(player_state);

            rtype::ScoreUpdate score_update;
            score_update.set_player_id(static_cast<uint32_t>(playerEntity));
            score_update.set_score(scoreComponent.score);
            game_state.add_scores()->CopyFrom(score_update);
        }
    }
}

void NetworkManager::addEnemyStatesToGameState(
    rtype::GameState& game_state, entt::registry& registry
)
{
    auto view = registry.view<EnemyAIComponent, TransformComponent, HealthComponent>();

    for (auto entity : view) {
        auto& transformComponent = view.get<TransformComponent>(entity);
        auto& healthComponent = view.get<HealthComponent>(entity);

        rtype::EnemyState enemy_state;
        enemy_state.set_enemy_id(static_cast<uint32_t>(entity));
        enemy_state.set_pos_x(transformComponent.x);
        enemy_state.set_pos_y(transformComponent.y);
        enemy_state.set_health(healthComponent.healthPoints);
        enemy_state.set_type("Normal");  // TODO : see with other how we deal with type of weapons

        game_state.add_enemies()->CopyFrom(enemy_state);
    }
}

void NetworkManager::sendGameStateToAllSessions(const rtype::GameState& game_state)
{
    rtype::Payload payload;
    payload.mutable_game_state()->CopyFrom(game_state);

    std::string serialized_state;
    payload.SerializeToString(&serialized_state);

    std::cout << "Sending game state: " << payload.DebugString() << std::endl;

    for (const auto& [endpoint, session] : _sessions) {
        std::cout << GREEN << "Sending game state to: " << endpoint << RESET << std::endl;
        _socket.async_send_to(
            boost::asio::buffer(serialized_state), session->endpoint(),
            [this](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
                handle_send(error);
            }
        );
    }
}

void NetworkManager::broadcast_game_state()
{
    rtype::GameState game_state;
    entt::registry& registry = _entityManager.getRegistry();

    addPlayerStateToGameState(game_state, registry);

    addEnemyStatesToGameState(game_state, registry);

    sendGameStateToAllSessions(game_state);
}
