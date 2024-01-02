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
    boost::asio::io_context _io_context;
    int _score = 0;

    // ! Managers
    InputManager _inputManager;
    NetworkManager _networkManager;
    PlayerProfileManager _playerProfileManager;
    ResourceManager _resourceManager;
    SceneManager _sceneManager;
    SettingsManager _settingsManager;

    EntityFactory _entityFactory;

public:
    /**
     * \brief Constructor for GameManager.
     * \param server_ip IP address for the server.
     * \param server_port Port number for the server.
     */
    GameManager(std::string server_ip, unsigned short server_port)
        : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Type-Revival"),
          _inputManager(_registry, _window),
          _networkManager(_io_context, server_ip, server_port),
          _playerProfileManager(),
          _resourceManager(),
          _sceneManager(_inputManager),
          _settingsManager(_resourceManager),
          _entityFactory(_registry, _resourceManager, _window)
    {
        _window.setFramerateLimit(60);
        std::cout << "GameManager created!" << std::endl;
    }

    ~GameManager() = default;

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

    void start_game()
    {
        _entityFactory.createMainMenu();
        _entityFactory.createWinScene();
        _entityFactory.createLoseScene();
        auto playerEntity = _entityFactory.createPlayer();
        _playerProfileManager.setPlayerEntity(playerEntity);
        _entityFactory.createBackground();
    };

    void parallaxSystem(float deltaTime);

    void makeAllAnimations();

    void makeHoldAnimation(entt::entity& entity, sf::IntRect rectangle);

    void makeSingleAnimation(entt::entity& entity, sf::IntRect rectangle);

    void makeInfiniteAnimation(entt::entity& entity, sf::IntRect rectangle);

    void game_loop()
    {
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
                    _inputManager.processKeyPress(event);
                    _inputManager.processKeyRelease(event);
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
            processPlayerActions(deltaTime.asSeconds());
            if (enemyClock.getElapsedTime().asSeconds() > 0.5f && _sceneManager.getCurrentScene() == GameScenes::InGame) {
                enemyClock.restart();
                float randomSpeed = getRandomFloat(2.0f, 5.0f);
                float randomY = getRandomFloat(0.0f, WINDOW_HEIGHT - 64.0f);
                _entityFactory.createNormalEnemy(randomY, randomSpeed);
            }
            _window.clear();
            parallaxSystem(deltaTime.asSeconds());
            enemySystem(explosionSound.sound);
            renderSystem();
            projectileSystem();
            collisionProjectileAndEnemy();
            makeAllAnimations();
            collisionEnemyAndPlayer();
            checkWin();
            _window.display();
        }
    }

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

    void collisionEnemyAndPlayer() {
        auto enemies = _registry.view<EnemyAIComponent, RenderableComponent>();
        auto player = _playerProfileManager.getPlayerEntity();
        for (auto& enemy : enemies) {
            sf::Sprite& enemySprite = enemies.get<RenderableComponent>(enemy).sprite;
            sf::Sprite& playerSprite = enemies.get<RenderableComponent>(player).sprite;
            if (enemySprite.getGlobalBounds().intersects(playerSprite.getGlobalBounds())) {
                deleteAIEnemies();
                _score = 0;
                _sceneManager.setCurrentScene(GameScenes::Lose);
            }
        }
    }

    void checkWin() {
        if (_score >= 20) {
            deleteAIEnemies();
            _score = 0;
            _sceneManager.setCurrentScene(GameScenes::Win);
        }
    }

    void deleteAIEnemies() {
        auto enemies = _registry.view<EnemyAIComponent>();
        for (auto enemy : enemies) {
            _registry.destroy(enemy);
        }
    }

    void processPlayerActions(float deltaTime)
    {
        auto& actions = _inputManager.getKeyboardActions();
        auto playerEntity = _playerProfileManager.getPlayerEntity();

        if (!_registry.all_of<TransformComponent>(playerEntity)) {
            printf(
                "Player entity does not have a "
                "TransformComponent\n"
            );
            return;
        }
        auto& transform = _registry.get<TransformComponent>(playerEntity);
        if (actions.Up == true && transform.y >= 0.0f) {
            transform.y -= 500.0f * deltaTime;
        }
        if (actions.Down == true && transform.y <= WINDOW_HEIGHT) {
            transform.y += 500.0f * deltaTime;
        }
        if (actions.Right == true && transform.x <= WINDOW_WIDTH) {
            transform.x += 500.0f * deltaTime;
        }
        if (actions.Left == true && transform.x >= 0.0f) {
            transform.x -= 500.0f * deltaTime;
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
