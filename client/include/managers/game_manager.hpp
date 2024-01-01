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
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

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

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class GameManager {
private:
    // Game
    string _assetsPath = ASSETS_DIR;
    sf::RenderWindow _window;
    entt::registry _registry;
    sf::Clock clock;
    sf::Clock enemyClock;

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
            case GameScenes::Credits:
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
    GameManager()
        : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Type-Revival"),
          _inputManager(),
          _networkManager(),
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
        //_entityFactory.createMainMenu();
        _entityFactory.createPlayer();
        _entityFactory.createBackground();
    }

    void parallaxSystem(float deltaTime)
    {
        auto view = _registry.view<
            ParallaxComponent, RenderableComponent, TransformComponent>();

        for (auto entity : view) {
            auto& parallax = view.get<ParallaxComponent>(entity);
            auto& renderable = view.get<RenderableComponent>(entity);
            auto& transform = view.get<TransformComponent>(entity);

            transform.x -= parallax.speed * deltaTime;

            if (transform.x < -WINDOW_WIDTH) {
                transform.x = 0.0f;
            }

            renderable.sprite.setPosition(sf::Vector2f(transform.x, transform.y)
            );
        }
    };

    void game_loop()
    {
        while (_window.isOpen()) {
            sf::Time deltaTime = clock.restart();
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
                if (isInputEvent(event)) {
                    _inputManager.processInput(event);
                }
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Space) {
                    entt::entity player =
                        _playerProfileManager.getPlayerEntity();
                    const sf::Vector2f& playerPosition =
                        _registry.get<RenderableComponent>(player)
                            .sprite.getPosition();
                    _entityFactory.createProjectile(
                        1.0f, 0.0f, playerPosition.x + 130.0f,
                        playerPosition.y + 64.0f, 5.0f
                    );
                }
            }
            if (enemyClock.getElapsedTime().asSeconds() > 0.5f) {
                enemyClock.restart();
                float randomSpeed = getRandomFloat(2.0f, 5.0f);
                float randomY = getRandomFloat(0.0f, WINDOW_HEIGHT - 64.0f);
                _entityFactory.createNormalEnemy(randomY, randomSpeed);
            }
            _window.clear();
            parallaxSystem(deltaTime.asSeconds());
            enemySystem();
            renderSystem();
            projectileSystem();
            collisionProjectileAndEnemy();
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

    void enemySystem()
    {
        auto enemies = _registry.view<
            EnemyAIComponent, RenderableComponent, VelocityComponent,
            HealthComponent>();
        std::vector<entt::entity> entitiesToDestroy;
        for (auto& entity : enemies) {
            auto& enemy = enemies.get<RenderableComponent>(entity);
            auto& velocity = enemies.get<VelocityComponent>(entity);
            float& health = enemies.get<HealthComponent>(entity).healthPoints;
            sf::Vector2f enemyPosition = enemy.sprite.getPosition();

            if (enemyPosition.x < -128.0f || health <= 0.0f) {
                entitiesToDestroy.push_back(entity);
            } else {
                enemy.sprite.setPosition(sf::Vector2f(
                    enemyPosition.x + velocity.dx * velocity.speed,
                    enemyPosition.y + velocity.dy * velocity.speed
                ));
            }
        }
        for (auto entity : entitiesToDestroy) {
            _registry.destroy(entity);
            printf("Entity Deleted\n");
        }
    }

    void projectileSystem()
    {
        auto projectiles =
            _registry
                .view<RenderableComponent, DamageComponent, VelocityComponent>(
                );
        std::vector<entt::entity> entitiesToDestroy;
        for (auto& entity : projectiles) {
            auto& projectile = projectiles.get<RenderableComponent>(entity);
            auto& velocity = projectiles.get<VelocityComponent>(entity);
            sf::Vector2f projectilePosition = projectile.sprite.getPosition();
            if (projectilePosition.x > WINDOW_WIDTH ||
                projectilePosition.x < -64.0f) {
                entitiesToDestroy.push_back(entity);
            } else {
                projectile.sprite.setPosition(sf::Vector2f(
                    projectilePosition.x + velocity.dx * velocity.speed,
                    projectilePosition.y + velocity.dy * velocity.speed
                ));
            };
        }
        for (auto entity : entitiesToDestroy) {
            _registry.destroy(entity);
            printf("Projectile Deleted\n");
        }
    }

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
            auto& sceneComponent = view.get<SceneComponent>(entity);
            // printf("Scene: %d\n", sceneComponent.scene.value_or(-1));
            if (sceneComponent.scene.has_value() &&
                sceneComponent.scene == _sceneManager.getCurrentScene()) {
                auto& renderable = view.get<RenderableComponent>(entity);

                if (renderable.text.getFont()) {
                    _window.draw(renderable.text);
                }
                if (renderable.sprite.getTexture()) {
                    _window.draw(renderable.sprite);
                    // sf::FloatRect hitbox = renderable.sprite.getGlobalBounds();
                    // sf::RectangleShape hitboxShape(sf::Vector2f(hitbox.width, hitbox.height));
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
