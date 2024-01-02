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

class GameManager {
private:
    // Game
    string _assetsPath = ASSETS_DIR;
    sf::RenderWindow _window;
    entt::registry _registry;
    sf::Clock clock;
    sf::Clock enemyClock;
    boost::asio::io_context _io_context;

    // ! Managers
    InputManager _inputManager;
    NetworkManager _networkManager;
    PlayerProfileManager _playerProfileManager;
    ResourceManager _resourceManager;
    SceneManager _sceneManager;
    SettingsManager _settingsManager;

    EntityFactory _entityFactory;

    static std::string getSceneName(GameScenes scene)
    {
        switch (scene) {
            case GameScenes::MainMenu:
                return "MainMenu";
                break;
            case GameScenes::InGame:
                return "InGame";
                break;
            case GameScenes::GameOver:
                return "GameOver";
                break;
            case GameScenes::Settings:
                return "Settings";
                break;
            case GameScenes::Tutorial:
                return "Credits";
                break;
            case GameScenes::Quit:
                return "Quit";
                break;
            case GameScenes::PauseMenu:
                return "PauseMenu";
                break;
            default:
                return "Unknown";
                break;
        }
    }

public:
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
        sound.setVolumeLevel(2.5f);
        SoundComponent explosionSound(*explosionSoundBuffer);
        explosionSound.setVolumeLevel(5.0f);
        SoundComponent musicSound(*musicSoundBuffer);
        musicSound.setVolumeLevel(10.0f);
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
            }
            if (musicSound.sound.getStatus() == sf::Music::Stopped) {
                musicSound.sound.play();
            }
            processPlayerActions(deltaTime.asSeconds());
            if (enemyClock.getElapsedTime().asSeconds() > 0.5f) {
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

    void projectileSystem()
    {
        auto projectiles = _registry.view<
            RenderableComponent, DamageComponent, VelocityComponent,
            TransformComponent>();
        std::vector<entt::entity> entitiesToDestroy;
        for (auto& entity : projectiles) {
            auto& projectile = projectiles.get<RenderableComponent>(entity);
            auto& velocity = projectiles.get<VelocityComponent>(entity);
            auto& postion = projectiles.get<TransformComponent>(entity);
            sf::Vector2f projectilePosition = projectile.sprite.getPosition();
            if (projectilePosition.x > WINDOW_WIDTH ||
                projectilePosition.x < -64.0f) {
                entitiesToDestroy.push_back(entity);
            } else {
                postion.x = projectilePosition.x + velocity.dx * velocity.speed;
                postion.y = projectilePosition.y + velocity.dy * velocity.speed;
            };
        }
        for (auto entity : entitiesToDestroy) {
            _registry.destroy(entity);
            printf("Projectile Deleted\n");
        }
    }

    void enemySystem(sf::Sound& explosionSound);

    void renderSystem()
    {
        // debugPrintCurrentScene();
        // _scene_manager.getCurrentSceneName();
        auto view = _registry.view<RenderableComponent, SceneComponent>();
        for (auto entity : view) {
            auto& sceneComponent = view.get<SceneComponent>(entity);
            if (!sceneComponent.scene.has_value()) {
                auto& renderable = view.get<RenderableComponent>(entity);
                _window.draw(renderable.sprite);
            }
        }
        for (auto entity : view) {
            auto& renderable = view.get<RenderableComponent>(entity);
            auto& sceneComponent = view.get<SceneComponent>(entity);
            if (_registry.all_of<TransformComponent>(entity)) {
                auto& transform = _registry.get<TransformComponent>(entity);
                renderable.sprite.setPosition(
                    sf::Vector2f(transform.x, transform.y)
                );
            }

            if (sceneComponent.scene.has_value() &&
                sceneComponent.scene == _sceneManager.getCurrentScene()) {

                if (renderable.text.getFont()) {
                    _window.draw(renderable.text);
                }
                if (renderable.sprite.getTexture()) {
                    _window.draw(renderable.sprite);
                    // sf::FloatRect hitbox = renderable.sprite.getGlobalBounds();
                    // sf::RectangleShape hitboxShape(
                    //     sf::Vector2f(hitbox.width, hitbox.height)
                    // );
                    // hitboxShape.setPosition(hitbox.left, hitbox.top);
                    // hitboxShape.setFillColor(sf::Color(0, 0, 0, 0));
                    // hitboxShape.setOutlineColor(sf::Color::Red);
                    // hitboxShape.setOutlineThickness(2.0f);
                    // _window.draw(hitboxShape);
                }
            }
        }
    }

    bool isInputEvent(const sf::Event& event)
    {
        // TODO: Add more input events if needed define scope with gars
        return event.type == sf::Event::KeyPressed ||
               event.type == sf::Event::KeyReleased ||
               event.type == sf::Event::MouseButtonPressed ||
               event.type == sf::Event::MouseButtonReleased;
    }

    void debugPrintCurrentScene() const
    {
        GameScenes currentScene = _sceneManager.getCurrentScene();
        std::string sceneName = getSceneName(currentScene);
        std::cout << "Current scene: " << sceneName << std::endl;
    };
};

#endif  // GAME_MANAGER_HPP
