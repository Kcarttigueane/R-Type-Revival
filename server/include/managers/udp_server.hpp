#if !defined(UPD_SERVER_HPP)
#    define UPD_SERVER_HPP

#    include <boost/array.hpp>
#    include <boost/asio.hpp>
#    include <boost/bind/bind.hpp>
#    include <ctime>
#    include <iostream>
#    include <map>
#    include <string>

#    include "../../../libs/EnTT/entt.hpp"

#    include "../../src/proto/r_type.pb.h"

// Managers

#    include "../utils.hpp"
#    include "./entity_manager.hpp"

using boost::asio::ip::udp;

class PlayerSession {
private:
    udp::endpoint endpoint_;
    entt::entity _playerEntity;

public:
    PlayerSession(udp::endpoint endpoint, entt::entity playerEntity)
        : endpoint_(endpoint), _playerEntity(playerEntity)
    {
        std::cout << MAGENTA << "PlayerSession created for endpoint: " << endpoint_
                  << " with Player entity: " << static_cast<uint32_t>(_playerEntity) << RESET
                  << std::endl;
    }

    udp::endpoint endpoint() const { return endpoint_; }

    entt::entity getPlayerEntity() const { return _playerEntity; }
};

class NetworkManager {
private:
    // Networking Data
    udp::socket _socket;
    udp::endpoint _remote_endpoint;
    boost::array<char, 1024> _recv_buffer;
    std::map<udp::endpoint, std::shared_ptr<PlayerSession>> _sessions;

    // Game Data
    std::uint32_t _next_player_id = 1;
    EntityManager& _entityManager;

    void start_receive()
    {
        _socket.async_receive_from(
            boost::asio::buffer(_recv_buffer), _remote_endpoint,
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                handle_receive(error, bytes_transferred);
            }
        );
    }

    void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (error) {
            std::cerr << "Receive error: " << error.message() << std::endl;
            return;
        }

        std::cout << "udp::endpoint" << _remote_endpoint << std::endl;
        std::cout << "Remote endpoint: " << _remote_endpoint.address() << ":"
                  << _remote_endpoint.port() << std::endl;

        std::string received_data(_recv_buffer.data(), bytes_transferred);
        rtype::Payload payload;

        if (payload.ParseFromString(received_data)) {
            std::cout << "Received payload: " << payload.DebugString() << std::endl;
            if (payload.has_connect()) {
                handle_connection_request(payload.connect());
            } else if (payload.has_event()) {
                handle_event(payload.event(), _remote_endpoint);
            } else if (payload.has_game_state()) {
                std::cerr << "Received game state from client." << std::endl;
            } else {
                std::cerr << "Unknown payload type received." << std::endl;
            }
        } else {
            std::cerr << "Failed to parse received data as protobuf Payload message." << std::endl;
        }
        start_receive();
    }

    // ! PLAYER CONNECTION
    void send_connection_response(std::uint32_t player_id);
    void handle_connection_request(const rtype::Connect& connect_message);

    void handle_event(const rtype::Event& event, const udp::endpoint& sender_endpoint)
    {
        auto session_it = _sessions.find(sender_endpoint);
        if (session_it != _sessions.end()) {
            auto& session = session_it->second;
            entt::entity playerEntity = session.get()->getPlayerEntity();

            TransformComponent& transformComponent =
                _entityManager.getRegistry().get<TransformComponent>(playerEntity);

            // Process the event
            switch (event.event()) {
                case rtype::EventType::MOVE_UP:
                    std::cout << "MOVE_UP" << std::endl;
                    transformComponent.y -= 10;
                    break;
                case rtype::EventType::MOVE_DOWN:
                    transformComponent.y += 10;
                    break;
                case rtype::EventType::MOVE_LEFT:
                    transformComponent.x -= 10;
                    break;
                case rtype::EventType::MOVE_RIGHT:
                    transformComponent.x += 10;
                    break;
                case rtype::EventType::SHOOT:
                    std::cout << "SHOOT" << std::endl;
                    // TODO : should create a bullet component
                    break;
                case rtype::EventType::QUIT:
                    std::cout << "QUIT" << std::endl;
                    // TODO : should disconnect the player
                    handle_player_quit(session, playerEntity);
                    break;
                default:
                    std::cerr << "Unknown event type." << std::endl;
                    break;
            }

            // Optionally, update other players about this move
            // broadcast_player_state(session);
        } else {
            std::cerr << "Session not found for endpoint: " << sender_endpoint << std::endl;
        }
    }

    void handle_player_quit(std::shared_ptr<PlayerSession>& session, entt::entity playerEntity)
    {
        std::cout << "Player " << static_cast<uint32_t>(playerEntity) << " quit the game."
                  << std::endl;

        _entityManager.getRegistry().destroy(playerEntity);
        _sessions.erase(session->endpoint());
    }

    void handle_send(const boost::system::error_code& error)
    {
        if (error) {
            std::cerr << "Send error: " << error.message() << std::endl;
        }
        // Additional code for successful send, if needed
    }

public:
    NetworkManager(boost::asio::io_context& io_context, int port, EntityManager& entityManager)
        : _socket(io_context, udp::endpoint(udp::v4(), port)), _entityManager(entityManager)
    {
        std::cout << "NetworkManager running at " << _socket.local_endpoint() << std::endl;
        start_receive();
    }

    ~NetworkManager() { _socket.close(); }

    // ! Broadcast GameState Payload:
    void addPlayerStateToGameState(rtype::GameState& game_state, entt::registry& registry);
    void addEnemyStatesToGameState(rtype::GameState& game_state, entt::registry& registry);
    void sendGameStateToAllSessions(const rtype::GameState& game_state);
    void broadcast_game_state();
};

#endif  // UPD_SERVER_HPP
