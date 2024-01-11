#if !defined(GAME_MANGER_HPP)
#    define GAME_MANGER_HPP

#    include <thread>

#    include "../game_metadata.hpp"
#    include "./entity_manager.hpp"
#    include "./network_manager.hpp"
#    include "./players_session_manager.hpp"

#    include "../../../common/utils/id_generator.hpp"

class GameManager {
private:
    boost::asio::io_context _io_context;
    // std::thread _network_thread;
    std::jthread _network_thread;

    // ! Game metadata
    GameMetadata _game_metadata;

    // ! Managers
    EntityManager _entity_manager;
    NetworkManager _network_manager;

    // ! ID generator
    IdGenerator _idGenerator;

public:
    GameManager(const std::string& server_address, std::string port);

    ~GameManager();

    void run();

    void game_loop();

    void velocitySystem();
};

#endif  // GAME_MANGER_HPP
