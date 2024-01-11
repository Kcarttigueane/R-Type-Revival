#include "../../include/managers/network_manager.hpp"

void NetworkManager::handle_receive(
    const boost::system::error_code& error, std::size_t bytes_transferred
)
{
    if (error) {
        std::cerr << "Receive error: " << error.message() << std::endl;
        return;
    }

    std::cout << "udp::endpoint" << _remote_endpoint << std::endl;
    std::cout << "Remote endpoint: " << _remote_endpoint.address() << ":" << _remote_endpoint.port()
              << std::endl;

    std::string received_data(_recv_buffer.data(), bytes_transferred);
    rtype::Payload payload;

    if (payload.ParseFromString(received_data)) {
        std::cout << "Received payload: " << payload.DebugString() << std::endl;
        if (payload.has_connect()) {
            handle_connection_request(payload.connect());
        } else if (payload.has_event()) {
            handle_event(payload.event(), _remote_endpoint);
        } else {
            std::cerr << "Unknown payload type received." << std::endl;
        }
    } else {
        std::cerr << "Failed to parse received data as protobuf Payload message." << std::endl;
    }
    start_receive();
}

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
    if (_sessions.find(_remote_endpoint) != _sessions.end()) {
        std::cerr << "Connection request ignored: Session already exists for endpoint "
                  << _remote_endpoint << std::endl;
        return;
    }

    if (_sessions.size() >= MAX_NUMBER_OF_PLAYERS) {
        std::cout << "Connection request rejected (Server Full): " << connect_message.player_name()
                  << std::endl;
        send_connection_response(false, 0);
        return;
    }

    std::cout << "Connection request from: " << connect_message.player_name() << std::endl;

    std::uint32_t player_id = _idGenerator.generateId();
    std::cout << YELLOW << "ID generated " << player_id << RESET << std::endl;

    entt::entity playerEntityId = static_cast<entt::entity>(player_id);
    entt::entity player = _entityManager.createPlayer(playerEntityId);

    auto session = std::make_shared<PlayerSession>(_remote_endpoint, player);
    _sessions[_remote_endpoint] = session;

    send_connection_response(true, player_id);
}

void NetworkManager::handle_player_projectile_creation(
    std::shared_ptr<PlayerSession>& session, entt::entity playerEntity
)
{
    std::cout << "Creating projectile" << std::endl;
    TransformComponent playerTransform =
        _entityManager.getRegistry().get<TransformComponent>(playerEntity);
    std::uint32_t bulletId = _idGenerator.generateId();
    entt::entity bulletEntityId = static_cast<entt::entity>(bulletId);
    entt::entity projectile = _entityManager.createProjectile(
        bulletEntityId, 1.0f, 0.0f, playerTransform.x + 50.0f, playerTransform.y, 25.0f,
        EntityType::PLAYER, static_cast<uint32_t>(playerEntity)
    );
}

void NetworkManager::handle_event(const rtype::Event& event, const udp::endpoint& sender_endpoint)
{
    auto session_it = _sessions.find(sender_endpoint);
    if (session_it != _sessions.end()) {
        auto& session = session_it->second;
        entt::entity playerEntity = session.get()->getPlayerEntity();

        TransformComponent& transformComponent =
            _entityManager.getRegistry().get<TransformComponent>(playerEntity);

        switch (event.event()) {
            case rtype::EventType::MOVE_UP:
                if (transformComponent.y > 0) {
                    transformComponent.y -= 10;
                }
                break;
            case rtype::EventType::MOVE_DOWN:
                if (transformComponent.y < WINDOW_HEIGHT) {
                    transformComponent.y += 10;
                }
                break;
            case rtype::EventType::MOVE_LEFT:
                if (transformComponent.x > 0) {
                    transformComponent.x -= 10;
                }
                break;
            case rtype::EventType::MOVE_RIGHT:
                if (transformComponent.x < WINDOW_WIDTH) {
                    transformComponent.x += 10;
                }
                break;
            case rtype::EventType::SHOOT:
                std::cout << "SHOOT" << std::endl;
                handle_player_projectile_creation(session, playerEntity);
                break;
            case rtype::EventType::QUIT:
                std::cout << "QUIT" << std::endl;
                handle_player_quit(session, playerEntity);
                break;
            default:
                std::cerr << "Unknown event type." << std::endl;
                break;
        }

        // Optionally, update other players about this move
        // broadcast_player_state();
    } else {
        std::cerr << "Session not found for endpoint: " << sender_endpoint << std::endl;
    }
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

void NetworkManager::addBulletStatesToGameState(
    rtype::GameState& gameState, entt::registry& registry
)
{
    auto view = registry.view<
        VelocityComponent, TransformComponent, DamageComponent, BulletTypeComponent,
        OwnerComponent>();
    for (auto& entity : view) {
        TransformComponent& transformable = view.get<TransformComponent>(entity);
        VelocityComponent& velocity = view.get<VelocityComponent>(entity);
        DamageComponent& damage = view.get<DamageComponent>(entity);
        OwnerComponent& owner = view.get<OwnerComponent>(entity);
        rtype::BulletState bulletState;
        bulletState.set_bullet_id(static_cast<uint32_t>(entity));
        bulletState.set_pos_x(transformable.x);
        bulletState.set_pos_y(transformable.y);
        bulletState.set_direction_x(velocity.dx);
        bulletState.set_direction_y(velocity.dy);
        bulletState.set_speed(velocity.speed);
        bulletState.set_owner_id(owner.id);
        gameState.add_bullets()->CopyFrom(bulletState);
    }
}

void NetworkManager::sendGameStateToAllSessions(const rtype::GameState& game_state)
{
    rtype::Payload payload;
    payload.mutable_game_state()->CopyFrom(game_state);

    std::string serialized_state;
    payload.SerializeToString(&serialized_state);

    // std::cout << "Sending game state: " << payload.DebugString() << std::endl;

    for (const auto& [endpoint, session] : _sessions) {
        // std::cout << GREEN << "Sending game state to: " << endpoint << RESET << std::endl;
        _socket.async_send_to(
            boost::asio::buffer(serialized_state), session->endpoint(),
            [this](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
                handle_send(error);
            }
        );
    }
}

void NetworkManager::addWaveStateToGameState(rtype::GameState& game_state)
{
    rtype::WaveState wave_state;
    wave_state.set_current_wave(1);
    wave_state.set_total_enemies(1);
    wave_state.set_wave_in_progress(true);

    game_state.mutable_wave_state()->CopyFrom(wave_state);

    rtype::Payload payload;

    payload.mutable_game_state()->CopyFrom(game_state);

    std::string serialized_state;

    payload.SerializeToString(&serialized_state);
}

void NetworkManager::broadcast_game_state()
{
    rtype::GameState game_state;
    entt::registry& registry = _entityManager.getRegistry();

    addPlayerStateToGameState(game_state, registry);

    addEnemyStatesToGameState(game_state, registry);

    addBulletStatesToGameState(game_state, registry);

    addWaveStateToGameState(game_state);

    sendGameStateToAllSessions(game_state);
}
