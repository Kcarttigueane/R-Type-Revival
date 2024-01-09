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

    // ! Managers
    InputManager _inputManager;
    NetworkManagerAsyncUDPClient _networkManager;
    PlayerProfileManager _playerProfileManager;
    ResourceManager _resourceManager;
    SceneManager _sceneManager;
    SettingsManager _settingsManager;

    EntityFactory _entityFactory;

    boost::asio::io_service& _io_service;

    std::set<uint32_t> _connectedPlayerIds;

    int _currentWaveLevel = 0;
    std::set<uint32_t> _enemiesIds;
    int _numberOfWaveEnemies = 0;
    bool _isWaveInProgress = false;

public:
    /**
     * \brief Constructor for GameManager.
     * \param server_ip IP address for the server.
     * \param server_port Port number for the server.
     */
    GameManager(
        std::string server_ip, std::string server_port, boost::asio::io_service& io_service
    );

    ~GameManager() { _registry.clear(); }

    void start_game();
    void game_loop();
    void handle_closing_game();

    // ! Collision and Event Handling methods

    void deleteAIEnemies();

    void processPlayerActions(float deltaTime)
    {
        auto& actions = _inputManager.getKeyboardActions();
        rtype::Event event;

        if (actions.Up == true) {
            rtype::Event event;
            event.set_event(rtype::EventType::MOVE_UP);

            rtype::Payload payload;
            payload.set_allocated_event(&event);

            _networkManager.send(payload);
        }
        if (actions.Down == true) {
            event.set_event(rtype::EventType::MOVE_DOWN);

            rtype::Payload payload;
            payload.set_allocated_event(&event);

            _networkManager.send(payload);
        }
        if (actions.Right == true) {
            event.set_event(rtype::EventType::MOVE_RIGHT);

            rtype::Payload payload;
            payload.set_allocated_event(&event);

            _networkManager.send(payload);
        }
        if (actions.Left == true) {
            event.set_event(rtype::EventType::MOVE_LEFT);

            rtype::Payload payload;
            payload.set_allocated_event(&event);

            _networkManager.send(payload);
        }
        if (actions.Shoot == true) {
            event.set_event(rtype::EventType::SHOOT);
            rtype::Payload payload;
            payload.set_allocated_event(&event);

            _networkManager.send(payload);
        }
    }

    // ! Server Response Processing:

    void processServerResponse()
    {
        std::queue<rtype::Payload> messages = _networkManager.getReceivedMessages();

        while (!messages.empty()) {
            rtype::Payload payload = messages.front();
            processPayload(payload);
            messages.pop();
        }
    }

    void processPayload(const rtype::Payload& payload)
    {
        std::cout << "Processing payload" << payload.DebugString() << std::endl;

        if (payload.has_connect_response()) {
            handleConnectResponse(payload);
        } else if (payload.has_game_state()) {
            handleGameState(payload);
        } else {
            std::cerr << "Unknown payload type received." << std::endl;
        }
    }

    void handleConnectResponse(const rtype::Payload& payload)
    {
        std::cout << "Connect response -> player Id: " << payload.connect_response().player_id()
                  << std::endl;
        std::cout << "Connect response -> Status " << payload.connect_response().status()
                  << std::endl;

        rtype::ConnectResponseStatus responseStatus = payload.connect_response().status();

        if (responseStatus == rtype::ConnectResponseStatus::SUCCESS) {
            std::cout << "Connect response -> OK" << std::endl;
            // TODO : should I check if the set can container max 4 players
            entt::entity player = static_cast<entt::entity>(payload.connect_response().player_id());
            auto playerEntity = _entityFactory.createPlayer(player);
            _connectedPlayerIds.insert(payload.connect_response().player_id());
        } else if (responseStatus == rtype::ConnectResponseStatus::SERVER_FULL) {
            std::cout << "Connect response  -> KO" << std::endl;
            return;
        } else {
            std::cout << "Connect response -> Unknown" << std::endl;
        }
    }

    void update_player_state(const rtype::GameState& game_state)
    {
        for (const auto& playerState : game_state.players()) {
            // TODO : should maybe check with my set of uint32_t if the player is already connected
            uint32_t playerID = playerState.player_id();
            float posX = playerState.pos_x();
            float posY = playerState.pos_y();
            float health = playerState.health();
            bool isShooting = playerState.is_shooting();

            std::cout << "Player " << playerID << ": Position(" << posX << ", " << posY
                      << "), Health: " << health << ", IsShooting: " << (isShooting ? "Yes" : "No")
                      << std::endl;

            entt::entity playerEntity = static_cast<entt::entity>(playerID);

            if (_registry.all_of<TransformComponent, HealthComponent, ScoreComponent>(playerEntity
                )) {
                auto& transformComponent = _registry.get<TransformComponent>(playerEntity);
                auto& healthComponent = _registry.get<HealthComponent>(playerEntity);
                auto& scoreComponent = _registry.get<ScoreComponent>(playerEntity);

                transformComponent.x = posX;
                transformComponent.y = posY;

                healthComponent.healthPoints = health;
            } else {
                std::cerr << "Entity with ID " << playerID << " does not have required components."
                          << std::endl;
            }
        }
    }

    void update_game_wave(const rtype::GameState& game_state)
    {
        if (game_state.has_wave_state()) {
            const rtype::WaveState& gameWave = game_state.wave_state();

            _currentWaveLevel = gameWave.current_wave();
            _numberOfWaveEnemies = gameWave.total_enemies();
            _isWaveInProgress = gameWave.wave_in_progress();

            std::cout << "Wave Info: Current Wave: " << _currentWaveLevel
                      << ", Total Enemies: " << _numberOfWaveEnemies
                      << ", Wave In Progress: " << (_isWaveInProgress ? "Yes" : "No") << std::endl;

            if (_isWaveInProgress) {
                if (_enemiesIds.size() < _numberOfWaveEnemies) {
                    for (const auto& enemyState : game_state.enemies()) {
                        const bool isIdAlreadyPresent =
                            _enemiesIds.contains(enemyState.enemy_id());  // ! C++20
                        std::cout << "isIdAlreadyPresent: " << isIdAlreadyPresent << std::endl;
                        if (!isIdAlreadyPresent) {
                            uint32_t enemyID = enemyState.enemy_id();
                            float posX = enemyState.pos_x();
                            float posY = enemyState.pos_y();
                            std::string type = enemyState.type();
                            float health = enemyState.health();

                            std::cout << "Enemy " << enemyID << ": Type(" << type << "), Position("
                                      << posX << ", " << posY << "), Health: " << health
                                      << std::endl;

                            entt::entity enemyEntity = static_cast<entt::entity>(enemyID);

                            if (_registry.all_of<TransformComponent, HealthComponent>(enemyEntity
                                )) {
                                auto& transformComponent =
                                    _registry.get<TransformComponent>(enemyEntity);
                                auto& healthComponent = _registry.get<HealthComponent>(enemyEntity);

                                transformComponent.x = posX;
                                transformComponent.y = posY;

                                healthComponent.healthPoints = health;

                            } else {
                                std::cerr << "Enemy entity with ID " << enemyID
                                          << " does not have required components." << std::endl;
                            }
                        }
                    }
                } else {
                    std::cout << "No enemies to create" << std::endl;
                }
            }
        } else {
            std::cerr << "Wave not in progress or no wave info." << std::endl;
        }
    }

    void update_player_score(const rtype::GameState& game_state)
    {
        for (const auto& playerScore : game_state.scores()) {
            uint32_t playerID = playerScore.player_id();
            uint32_t score = playerScore.score();

            std::cout << "Player " << playerID << ": Score: " << score << std::endl;

            entt::entity playerEntity = static_cast<entt::entity>(playerID);

            if (_registry.all_of<ScoreComponent>(playerEntity)) {
                auto& scoreComponent = _registry.get<ScoreComponent>(playerEntity);

                scoreComponent.score = score;

            } else {
                std::cerr << "Entity with ID " << playerID << " does not have required components."
                          << std::endl;
            }
        }
    }

    void handleGameState(const rtype::Payload& payload)
    {
        if (payload.has_game_state()) {
            const rtype::GameState& gameState = payload.game_state();

            update_player_state(gameState);
            update_player_score(gameState);
            // update_enemies_state(gameState);
            update_game_wave(gameState);
            // TODO : Continue for powerUps, scores, bullets, etc.
        } else {
            std::cerr << "Payload does not contain a GameState." << std::endl;
        }
    }

    // ! Systems:
    void projectileSystem();

    void enemySystem(sf::Sound& explosionSound);

    void renderSystem();

    void parallaxSystem(float deltaTime);

    void planetSystem(float deltaTime);

    void makeAllAnimations();

    void makeHoldAnimation(entt::entity& entity, sf::IntRect rectangle);

    void makeSingleAnimation(entt::entity& entity, sf::IntRect rectangle);

    void makeInfiniteAnimation(entt::entity& entity, sf::IntRect rectangle);

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
