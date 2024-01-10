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

    std::set<uint32_t> _connectedPlayerIds;

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

    // ! Collision and Event Handling methods

    void deleteAIEnemies();

    void processPlayerActions(float deltaTime);

    void send_event_to_server(rtype::EventType event_type);

    // ! Server Response Processing:

    void processServerResponse();

    void processPayload(const rtype::Payload& payload);

    void handleConnectResponse(const rtype::Payload& payload);

    void update_player_state(const rtype::GameState& game_state);

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
            // update_player_score(gameState);
            // update_enemies_state(gameState);
            // update_game_wave(gameState);
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
