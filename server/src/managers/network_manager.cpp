#include "../../include/managers/udp_server.hpp"

void NetworkManager::send_connection_response(std::uint32_t player_id)
{
    rtype::ConnectResponse response;
    response.set_player_id(player_id);

    std::cout << "Sending connection response: " << response.DebugString() << std::endl;

    std::string serialized_response;
    response.SerializeToString(&serialized_response);

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
    std::cout << "Connection request from: " << connect_message.player_name() << std::endl;

    std::uint32_t player_id = _next_player_id++;

    entt::entity playerEntityId = static_cast<entt::entity>(player_id);
    entt::entity player = _entityManager.createPlayer(playerEntityId);

    auto session = std::make_shared<PlayerSession>(_remote_endpoint, player);
    _sessions[_remote_endpoint] = session;

    send_connection_response(player_id);
}
