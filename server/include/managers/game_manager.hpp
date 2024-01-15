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

/**
 * @file game_manager.hpp
 * @brief File containing the GameManager class.
 */

/**
 * @class GameManager
 * @brief Main controller for the game, handling game loop and systems.
 *
 * The GameManager class is responsible for initializing and controlling
 * the main game loop, managing entities, and handling user input and
 * interactions between different game systems.
 */
class GameManager {
private:
    boost::asio::io_context _io_context;
    std::jthread _network_thread;

    GameMetadata _game_metadata;

    EntityManager _entity_manager;
    NetworkManager _network_manager;
    WaveManager _wave_manager;

    IdGenerator _idGenerator;

public:
    /**
     * @brief Constructor for GameManager.
     * @param server_address IP address for the server.
     * @param port Port number for the server.
     */
    GameManager(const std::string& server_address, std::string port);

    /**
     * @brief Default destructor.
     */
    ~GameManager();

    /**
     * @brief Starts the game.
     */
    void run();

    /**
     * @brief Main game loop.
     */
    void game_loop();

    /**
     * @brief Updates the game logic.
     * @param deltaTime The time elapsed since the last frame.
     */
    void updateGameLogic(float deltaTime);

    /**
     * @brief Updates the velocity system.
     */
    void velocitySystem();

    void collisionProjectileAndEnemy();

    void deleteDeadEnemies();

    void makeEnemyShoot();

    void collisionPlayerAndEnemy();

    void collisionPlayerAndEnemyBullet();
};

#endif  // GAME_MANGER_HPP
