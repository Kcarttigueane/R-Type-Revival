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

    int _currentWaveLevel = 0;
    std::set<uint32_t> _enemiesIds;
    int _numberOfWaveEnemies = 0;
    bool _isWaveInProgress = false;

    std::jthread _network_thread;

public:
    /**
     * \brief Constructor for GameManager.
     * \param server_ip IP address for the server.
     * \param server_port Port number for the server.
     */
    GameManager(
        std::string server_ip, std::string server_port, boost::asio::io_service& io_service
    );

    ~GameManager() = default;

    void start_game();

    void game_loop();

    void handle_closing_game();

    void processEvents();

    // ! Collision and Event Handling methods

    void deleteAIEnemies();

    void processPlayerActions(float deltaTime);

    void send_event_to_server(rtype::EventType event_type);

    // ! Server Response Processing:

    void processServerResponse();

    void processPayload(const rtype::Payload& payload);

    void handleConnectResponse(const rtype::Payload& payload);

    void update_player_state(const rtype::GameState& game_state);

    void updateBulletState(const rtype::GameState& game_state);

    void update_game_wave(const rtype::GameState& game_state);

    void update_player_score(const rtype::GameState& game_state);

    void handleGameState(const rtype::Payload& payload);

    // ! Systems:

    void enemySystem(sf::Sound& explosionSound);

    void makeEnemyShoot();

    void renderSystem();

    void parallaxSystem(float deltaTime);

    void planetSystem(float deltaTime);

    void makeAllAnimations();

    void makeHoldAnimation(entt::entity& entity, sf::IntRect rectangle);

    void makeSingleAnimation(entt::entity& entity, sf::IntRect rectangle);

    void makeInfiniteAnimation(entt::entity& entity, sf::IntRect rectangle);

    void velocitySystem();

    // ! Utility methods
    /**
     * \brief Checks if an event is related to input.
     * \param event The SFML event to check.
     * \return True if the event is an input event, false otherwise.
     */
    bool isInputEvent(const sf::Event& event);

    void drawHitBox(RenderableComponent& renderable);
};

#endif  // GAME_MANAGER_HPP
