#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "../config.hpp"

// Managers
#include "./input_manager.hpp"
#include "./network_manager.hpp"
#include "./player_profile_manager.hpp"
#include "./resource_manager.hpp"
#include "./scene_manager.hpp"
#include "./settings_manager.hpp"

// Factories
#include "../entity_factory.hpp"

// Libraries

#include "../../../common/components/component_includes.hpp"
#include "../../../common/utils/id_generator.hpp"
#include "../../../libs/EnTT/entt.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <vector>

/**
 * \class GameManager
 * \brief Main controller for the game, handling game loop and systems.
 *
 * The GameManager class is responsible for initializing and controlling
 * the main game loop, managing entities, and handling user input and
 * interactions between different game systems.
 */
class GameManager {
private:
    string _assetsPath = ASSETS_DIR;
    sf::RenderWindow _window;
    entt::registry _registry;

    sf::Clock clock;
    sf::Clock enemyClock;
    sf::Clock transitionClock;
    sf::Clock sendEventClock;
    sf::Clock shootClock;

    // ! Managers
    InputManager _inputManager;
    NetworkManagerAsyncUDPClient _networkManager;
    PlayerProfileManager _playerProfileManager;
    ResourceManager _resourceManager;
    SceneManager _sceneManager;
    SettingsManager _settingsManager;

    EntityFactory _entityFactory;

    boost::asio::io_service& _io_service;

    // --------------------------------------
    // IF IMPROVABLE, IMPROVE! //

    SoundComponent _shootingSound;
    SoundComponent _explosionSound;
    SoundComponent _musicSound;

    // --------------------------------------

    std::set<uint32_t> _connectedPlayerIds;
    std::set<uint32_t> _bulletIds;
    std::set<uint32_t> _enemiesIds;

    int _currentWaveLevel = 0;
    bool _isWaveInProgress = false;

    std::jthread _network_thread;

    // ! Utility methods
    /**
     * \brief Checks if an event is related to input.
     * \param event The SFML event to check.
     * \return True if the event is an input event, false otherwise.
     */
    bool isInputEvent(const sf::Event& event);

public:
    /**
     * \brief Constructor for GameManager.
     * \param server_ip IP address for the server.
     * \param server_port Port number for the server.
     */
    GameManager(
        std::string server_ip, std::string server_port, boost::asio::io_service& io_service
    );

    /**
     * \brief Default destructor.
     */
    ~GameManager() = default;

    /**
     * \brief Starts the game.
     */
    void start_game();

    /**
     * \brief Main game loop.
     */
    void game_loop();

    /**
     * \brief Handles the game loop.
     */
    void handle_closing_game();

    /**
     * \brief Handles the game loop.
     */
    void processEvents();

    // ! Collision and Event Handling methods

    /**
     * \brief Handles the collision between two entities.
     */
    void deleteEnemies();

    /**
     * \brief Processes the player actions.
     *
     * \param deltaTime The time elapsed since the last frame.
     */
    void processPlayerActions(float deltaTime);

    /**
     * @brief Sends an event to the server.
     * @param event_type The type of the event to be sent.
     */
    void send_event_to_server(rtype::EventType event_type);

    /**
 * @brief Processes the server's response.
 */
    void processServerResponse();

    /**
     * @brief Processes a payload received from the server.
     * @param payload The payload to process.
     */
    void processPayload(const rtype::Payload& payload);

    /**
     * @brief Handles the response to a connection request.
     * @param payload The payload containing the connection response.
     */
    void handleConnectResponse(const rtype::Payload& payload);

    /**
     * @brief Updates the player's state based on the game state information.
     * @param game_state The GameState object containing player state information.
     */
    void update_player_state(const rtype::GameState& game_state);

    /**
     * @brief Updates the state of bullets based on the game state information.
     * @param game_state The GameState object containing bullet state information.
     */
    void updateBulletState(const rtype::GameState& game_state);

    /**
    * @brief Updates the game's wave information based on the game state.
    * @param game_state The GameState object containing wave information.
    */
    void update_game_wave(const rtype::GameState& game_state);

    /**
     * @brief Updates the player's score based on the game state.
     * @param game_state The GameState object containing score information.
     */
    void update_player_score(const rtype::GameState& game_state);

    /**
     * @brief Handles the GameState payload received from the server.
     * @param payload The payload containing the GameState.
     */
    void handleGameState(const rtype::Payload& payload);

    // ! Systems:

    /**
     * @brief Manages the enemy system, including interactions and behavior.
     * @param explosionSound The sound effect for enemy explosions.
     */
    void enemySystem(sf::Sound& explosionSound);

    /**
     * @brief Manages the rendering system for the game.
     */
    void renderSystem();

    /**
     * @brief Handles the parallax effect system based on delta time.
     * @param deltaTime The time elapsed since the last frame.
     */
    void parallaxSystem(float deltaTime);

    /**
     * @brief Manages the planet system, simulating planetary movements.
     * @param deltaTime The time elapsed since the last frame.
     */
    void planetSystem(float deltaTime);

    /**
     * @brief Triggers all animations for the game entities.
     */
    void makeAllAnimations();

    /**
     * @brief Manages the animation of the Wave title screen.
     */
    void makeWaveTransitionAnimation();

    /**
    * @brief Executes a hold animation for a given entity.
    * @param entity The entity to animate.
    * @param rectangle The frame rectangle for the animation.
    */
    void makeHoldAnimation(entt::entity& entity, sf::IntRect rectangle);

    /**
     * @brief Executes a single animation cycle for a given entity.
     * @param entity The entity to animate.
     * @param rectangle The frame rectangle for the animation.
     */
    void makeSingleAnimation(entt::entity& entity, sf::IntRect rectangle);

    /**
    * @brief Executes an infinite animation loop for a given entity.
    * @param entity The entity to animate.
    * @param rectangle The frame rectangle for the animation.
    */
    void makeInfiniteAnimation(entt::entity& entity, sf::IntRect rectangle);

    /**
    * @brief Manages the velocity system for game entities.
    */
    void velocitySystem();

    // ! Utility methods

    /**
     * @brief Draws the hit box for a renderable component.
     * @param renderable The renderable component to draw the hit box for.
     */
    void drawHitBox(RenderableComponent& renderable);
};

#endif  // GAME_MANAGER_HPP
