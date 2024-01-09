#if !defined(GAME_MANGER_HPP)
#    define GAME_MANGER_HPP

#    include "../game_metadata.hpp"
#    include "./entity_manager.hpp"
#    include "./network_manager.hpp"
#    include "./players_session_manager.hpp"

class GameManager {
private:
    boost::asio::io_context _io_context;
    std::thread _network_thread;

    // ! Game metadata
    GameMetadata _game_metadata;

    // ! Managers
    EntityManager _entity_manager;
    NetworkManager _network_manager;

public:
    GameManager(const std::string& server_address, std::string port)
        : _network_manager(_io_context, port, _entity_manager)
    {}

    ~GameManager() = default;

    void run()
    {
        _network_thread = std::thread([this]() { _io_context.run(); });
        game_loop();
    }

    void game_loop()
    {
        while (_game_metadata.isRunning) {
            // TODO : Deal with game updates

            static auto last_update = std::chrono::steady_clock::now();
            auto now = std::chrono::steady_clock::now();
            if (now - last_update >= std::chrono::milliseconds(1000)) {
                _network_manager.broadcast_game_state();
                last_update = now;
            }

            // TODO : Deal with game process -> enemies creations
        }
    }
};

#endif  // GAME_MANGER_HPP
