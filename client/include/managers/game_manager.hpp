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
    boost::asio::io_context _io_context;
    std::string _server_ip = "127.0.0.1";
    unsigned short _server_port = 8080;

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
    GameManager()
        : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Type-Revival"),
          _inputManager(_registry, _window),
          _networkManager(_io_context, _server_ip, _server_port),
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
    }

    void parallaxSystem(float deltaTime);

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
            enemySystem();
            renderSystem();
            _window.display();
        }
    }

    void processPlayerActions(float deltaTime)
    {
        auto& actionsQueue = _inputManager.getPlayerActionsQueue();
        while (!actionsQueue.empty()) {
            PlayerAction action = actionsQueue.front();
            actionsQueue.pop();

            auto playerEntity = _playerProfileManager.getPlayerEntity();

            if (!_registry.all_of<TransformComponent>(playerEntity)) {
                printf("Player entity does not have a TransformComponent\n");
                continue;
            }

            auto& transform = _registry.get<TransformComponent>(playerEntity);

            switch (action) {
                case PlayerAction::Shoot:
                    break;
                case PlayerAction::MoveLeft:
                    transform.x -= 10.0f;
                    break;
                case PlayerAction::MoveRight:
                    transform.x += 10.0f;
                    break;
                case PlayerAction::MoveUp:
                    transform.y -= 10.0f;
                    break;
                case PlayerAction::MoveDown:
                    transform.y += 10.0f;
                    break;
                default:
                    break;
            }
        }
    }

    void enemySystem();

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
