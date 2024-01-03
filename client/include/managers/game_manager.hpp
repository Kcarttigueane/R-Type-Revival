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
#include <random>
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
    // Game
    string _assetsPath = ASSETS_DIR;
    sf::RenderWindow _window;
    entt::registry _registry;
    sf::Clock clock;
    sf::Clock enemyClock;

    int _score = 0;

    // ! Managers
    InputManager _inputManager;
    // NetworkManager _networkManager;
    PlayerProfileManager _playerProfileManager;
    ResourceManager _resourceManager;
    SceneManager _sceneManager;
    SettingsManager _settingsManager;

    EntityFactory _entityFactory;

    std::set<uint32_t> _playerPresent;
    bool _isFirstPlayer = true;

    std::string _server_ip;
    unsigned short _server_port;

public:
    /**
     * \brief Constructor for GameManager.
     * \param server_ip IP address for the server.
     * \param server_port Port number for the server.
     */
    GameManager(std::string server_ip, unsigned short server_port)
        : _server_ip(server_ip),
          _server_port(server_port),
          _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Type-Revival"),
          _inputManager(_registry, _window),
          //   _networkManager(_io_context, server_ip, server_port),
          _playerProfileManager(),
          _resourceManager(),
          _sceneManager(_inputManager),
          _settingsManager(_resourceManager),
          _entityFactory(_registry, _resourceManager, _window)
    {
        _window.setFramerateLimit(60);
        std::cout << "GameManager created!" << std::endl;
    }

    ~GameManager()
    {
        _registry.clear();
        // Signal the client thread to stop

        // client_thread.join();
    }

    /**
     * \brief Generates a random float within a range.
     * \param min Minimum value of the range.
     * \param max Maximum value of the range.
     * \return Randomly generated float.
     */
    float getRandomFloat(float min, float max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distribution(min, max);
        return distribution(gen);
    }

    rtype::Event handle_key(sf::Keyboard::Key key)
    {
        rtype::Event event;
        switch (key) {
            case sf::Keyboard::Up:
                event.set_event(rtype::EventType::MOVEUP);
                break;
            case sf::Keyboard::Down:
                event.set_event(rtype::EventType::MOVEDOWN);
                break;
            case sf::Keyboard::Left:
                event.set_event(rtype::EventType::MOVELEFT);
                break;
            case sf::Keyboard::Right:
                event.set_event(rtype::EventType::MOVERIGHT);
                break;
            case sf::Keyboard::Space:
                event.set_event(rtype::EventType::SHOOT);
                break;
            default:
                break;
        }
        return event;
    }

    void start_game()
    {
        _entityFactory.createMainMenu();
        _entityFactory.createWinScene();
        _entityFactory.createLoseScene();
        _entityFactory.createBackground();

        std::queue<rtype::Event> messages;
        std::mutex messages_mutex;

        boost::asio::io_context io_context;
        ClientUDP client(io_context, _server_ip, _server_port);

        std::thread client_thread([&io_context, &client, &messages,
                                   &messages_mutex]() {
            while (true) {
                io_context.poll();  // Handle asynchronous operations

                // Check for stop request
                if (client.stop_requested_) {
                    std::cout << "Stopping client thread..." << std::endl;
                    rtype::Event event;
                    event.set_event(rtype::EventType::QUIT);
                    client.send_payload(event);
                    break;
                }

                // Send messages to the server
                {
                    std::lock_guard<std::mutex> lock(messages_mutex);
                    while (!messages.empty()) {
                        client.send_payload(messages.front());
                        messages.pop();
                    }
                }
            }
        });

        auto soundBuffer = _resourceManager.loadSoundBuffer(
            _assetsPath + "/sound_fx/shot2.wav"
        );
        auto explosionSoundBuffer = _resourceManager.loadSoundBuffer(
            _assetsPath + "/sound_fx/explosion.wav"
        );
        auto musicSoundBuffer = _resourceManager.loadSoundBuffer(
            _assetsPath + "/sound_fx/music.wav"
        );
        SoundComponent sound(*soundBuffer);
        sound.setVolumeLevel(1.5f);
        SoundComponent explosionSound(*explosionSoundBuffer);
        explosionSound.setVolumeLevel(7.5f);
        SoundComponent musicSound(*musicSoundBuffer);
        musicSound.setVolumeLevel(2.0f);
        musicSound.sound.play();
        while (_window.isOpen()) {
            sf::Time deltaTime = clock.restart();
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
                if (isInputEvent(event)) {
                    std::lock_guard<std::mutex> lock(messages_mutex);
                    messages.push(handle_key(event.key.code));
                    // _inputManager.processKeyPress(event);
                    // _inputManager.processKeyRelease(event);
                }
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Space) {
                    sound.playSound();

                    entt::entity player =
                        _playerProfileManager.getPlayerEntity();
                    const sf::Vector2f& playerPosition =
                        _registry.get<RenderableComponent>(player)
                            .sprite.getPosition();
                    _entityFactory.createProjectile(
                        1.0f, 0.0f, playerPosition.x + 145.0f,
                        playerPosition.y + 47.5f, 5.0f
                    );
                }
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape) {
                    _sceneManager.setCurrentScene(GameScenes::InGame);
                }
            }
            if (musicSound.sound.getStatus() == sf::Music::Stopped) {
                musicSound.sound.play();
            }
            auto payloads = client.get_payloads();
            for (auto payload : payloads) {

                std::cout << "Payload : " << payload.ShortDebugString()
                          << std::endl;
                if (_playerPresent.find(payload.identity()) ==
                    _playerPresent.end()) {
                    printf(
                        "Player %u joined the game\n",
                        static_cast<unsigned int>(payload.identity())
                    );
                    _playerPresent.insert(payload.identity());

                    entt::entity player =
                        static_cast<entt::entity>(payload.identity());
                    auto playerEntity = _entityFactory.createPlayer(player);
                    if (_isFirstPlayer) {
                        _playerProfileManager.setPlayerEntity(playerEntity);
                        _isFirstPlayer = false;
                    }
                }
                if (!_playerPresent.empty()) {
                    processPlayerActions(deltaTime.asSeconds());
                    // Update player position
                    entt::entity playerEntity =
                        static_cast<entt::entity>(payload.identity());

                    auto& transform =
                        _registry.get<TransformComponent>(playerEntity);
                    transform.x = payload.posx();
                    transform.y = payload.posy();

                    if (enemyClock.getElapsedTime().asSeconds() > 0.5f) {
                        enemyClock.restart();
                        float randomSpeed = getRandomFloat(2.0f, 5.0f);
                        float randomY =
                            getRandomFloat(0.0f, WINDOW_HEIGHT - 64.0f);
                        _entityFactory.createNormalEnemy(randomY, randomSpeed);
                    }
                }
            }
            // std::cout << "identity : " << payload.identity() << std::endl;
            // std::cout << "posx : " << payload.posx() << std::endl;
            // std::cout << "posy : " << payload.posy() << std::endl;

            _window.clear();
            parallaxSystem(deltaTime.asSeconds());

            if (!_playerPresent.empty()) {
                enemySystem(explosionSound.sound);
                renderSystem();
                projectileSystem();
                collisionProjectileAndEnemy();
                collisionEnemyAndPlayer();
                makeAllAnimations();
                checkWin();
            }
            // printf("Payload : %s\n", payload.

            _window.display();
        }

        client.stop();
        client_thread.join();
    }

    void parallaxSystem(float deltaTime);

    void makeAllAnimations();

    void makeHoldAnimation(entt::entity& entity, sf::IntRect rectangle);

    void makeSingleAnimation(entt::entity& entity, sf::IntRect rectangle);

    void makeInfiniteAnimation(entt::entity& entity, sf::IntRect rectangle);

    void game_loop(){};

    void collisionProjectileAndEnemy()
    {
        auto enemies =
            _registry
                .view<EnemyAIComponent, RenderableComponent, HealthComponent>();
        auto projectiles =
            _registry.view<RenderableComponent, DamageComponent>();

        for (auto& enemy : enemies) {
            sf::Sprite& enemySprite =
                enemies.get<RenderableComponent>(enemy).sprite;
            float& enemyHealth =
                enemies.get<HealthComponent>(enemy).healthPoints;
            for (auto& projectile : projectiles) {
                sf::Sprite& projectileSprite =
                    projectiles.get<RenderableComponent>(projectile).sprite;
                float projectileDamage =
                    projectiles.get<DamageComponent>(projectile).damage;
                if (enemySprite.getGlobalBounds().intersects(
                        projectileSprite.getGlobalBounds()
                    )) {
                    enemyHealth -= projectileDamage;
                    _registry.destroy(projectile);
                }
            }
        }
    }

    void collisionEnemyAndPlayer()
    {
        auto enemies = _registry.view<EnemyAIComponent, RenderableComponent>();
        auto player = _playerProfileManager.getPlayerEntity();
        for (auto& enemy : enemies) {
            sf::Sprite& enemySprite =
                enemies.get<RenderableComponent>(enemy).sprite;
            sf::Sprite& playerSprite =
                enemies.get<RenderableComponent>(player).sprite;
            if (enemySprite.getGlobalBounds().intersects(
                    playerSprite.getGlobalBounds()
                )) {
                deleteAIEnemies();
                _score = 0;
                _sceneManager.setCurrentScene(GameScenes::Lose);
            }
        }
    };

    void checkWin()
    {
        if (_score >= 20) {
            deleteAIEnemies();
            _score = 0;
            _sceneManager.setCurrentScene(GameScenes::Win);
        }
    }

    void deleteAIEnemies()
    {
        auto enemies = _registry.view<EnemyAIComponent>();
        for (auto enemy : enemies) {
            _registry.destroy(enemy);
        }
    }

    void processPlayerActions(float deltaTime)
    {
        auto& actions = _inputManager.getKeyboardActions();
        rtype::Event protoEvent;

        if (actions.Up == true) {
            protoEvent.set_event(rtype::EventType::MOVEUP);
        }
        if (actions.Down == true) {
            protoEvent.set_event(rtype::EventType::MOVEDOWN);
        }
        if (actions.Right == true) {
            protoEvent.set_event(rtype::EventType::MOVERIGHT);
        }
        if (actions.Left == true) {
            protoEvent.set_event(rtype::EventType::MOVELEFT);
        }
    }

    void projectileSystem();

    void enemySystem(sf::Sound& explosionSound);

    void renderSystem();

    /**
     * \brief Checks if an event is related to input.
     * \param event The SFML event to check.
     * \return True if the event is an input event, false otherwise.
     */
    bool isInputEvent(const sf::Event& event)
    {
        // TODO: Add more input events if needed define scope with gars
        return event.type == sf::Event::KeyPressed ||
               event.type == sf::Event::KeyReleased ||
               event.type == sf::Event::MouseButtonPressed ||
               event.type == sf::Event::MouseButtonReleased;
    }
};

#endif  // GAME_MANAGER_HPP
