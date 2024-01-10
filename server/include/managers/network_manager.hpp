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

#    include "../../../build/common/proto/r_type.pb.h"

// Managers

#    include "../config.hpp"
#    include "../utils.hpp"

#    include "./entity_manager.hpp"
#    include "./players_session_manager.hpp"

#    include "../../../common/utils/id_generator.hpp"

#    define BUFFER_SIZE 3000

#    define MAX_NUMBER_OF_PLAYERS 4

using boost::asio::ip::udp;

class NetworkManager {
private:
    // Networking Data
    udp::socket _socket;
    udp::endpoint _remote_endpoint;
    boost::array<char, BUFFER_SIZE> _recv_buffer;
    std::map<udp::endpoint, std::shared_ptr<PlayerSession>> _sessions;

    // Game Data
    std::uint32_t _next_player_id = 10;
    EntityManager& _entityManager;

    IdGenerator& _idGenerator;

    void start_receive()
    {
        _socket.async_receive_from(
            boost::asio::buffer(_recv_buffer), _remote_endpoint,
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                handle_receive(error, bytes_transferred);
            }
        );
    }

    void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);

    // ! PLAYER CONNECTION
    void send_connection_response(bool is_accepted, std::uint32_t player_id);
    void handle_connection_request(const rtype::Connect& connect_message);

    void handle_event(const rtype::Event& event, const udp::endpoint& sender_endpoint);

    void handle_player_quit(std::shared_ptr<PlayerSession>& session, entt::entity playerEntity);

    void send_message(const std::string& serialized_message, const udp::endpoint& target_endpoint)
    {
        _socket.async_send_to(
            boost::asio::buffer(serialized_message), target_endpoint,
            [this](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
                handle_send(error);
            }
        );
    }

    void handle_send(const boost::system::error_code& error)
    {
        if (error) {
            std::cerr << "Send error: " << error.message() << std::endl;
        }
    }

public:
    NetworkManager(
        boost::asio::io_context& io_context, std::string port, EntityManager& entityManager,
        IdGenerator& idGenerator
    )
        : _socket(io_context, udp::endpoint(udp::v4(), std::stoi(port))),
          _entityManager(entityManager),
          _idGenerator(idGenerator)
    {
        std::cout << "NetworkManager running at " << _socket.local_endpoint() << std::endl;
        start_receive();
    }

    ~NetworkManager() { _socket.close(); }

    // ! Broadcast GameState Payload:
    void addPlayerStateToGameState(rtype::GameState& game_state, entt::registry& registry);
    void addEnemyStatesToGameState(rtype::GameState& game_state, entt::registry& registry);
    void addWaveStateToGameState(rtype::GameState& game_state);
    void sendGameStateToAllSessions(rtype::GameState& game_state);
    void broadcast_game_state(rtype::GameState& gameState);
};

#endif  // UPD_SERVER_HPP
