#if !defined(GAME_MANGER_HPP)
#    define GAME_MANGER_HPP

#    include <thread>

#    include "../game_metadata.hpp"
#    include "./entity_manager.hpp"
#    include "./network_manager.hpp"
#    include "./players_session_manager.hpp"
#    include "./wave_manager.hpp"

#    include "../../../common/utils/id_generator.hpp"

#    include <chrono>

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
    WaveManager _wave_manager;

    // ! ID generator
    IdGenerator _idGenerator;

public:
    GameManager(const std::string& server_address, std::string port);

    ~GameManager();

    void run();

    void game_loop();

    void updateGameLogic(float deltaTime);

    void velocitySystem();

    void collisionProjectileAndEnemy();

    void deleteDeadEnemies();

    void makeEnemyShoot();

    void collisionPlayerAndEnemy();

    void collisionPlayerAndEnemyBullet();
};

#endif  // GAME_MANGER_HPP
