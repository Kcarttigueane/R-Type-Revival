#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

// Managers
#include "./input_manager.hpp"
#include "./network_manager.hpp"
#include "./player_profile_manager.hpp"
#include "./resource_manager.hpp"
#include "./scene_manager.hpp"
#include "./settings_manager.hpp"

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

#include <iostream>

#define WINDOW_WIDTH 1980
#define WINDOW_HEIGHT 1080

class GameManager {
private:
    // Game
    string _assetsPath = ASSETS_DIR;
    sf::RenderWindow _window;
    entt::registry _registry;
    sf::Clock clock;

    // ! Managers
    InputManager _input_manager;
    NetworkManager _network_manager;
    PlayerProfileManager _player_profile_manager;
    ResourceManager _resource_manager;
    SceneManager _scene_manager;
    SettingsManager _settings_manager;

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
          _input_manager(),
          _network_manager(),
          _player_profile_manager(),
          _resource_manager(),
          _scene_manager(_input_manager),
          _settings_manager(_resource_manager)
    {
        _window.setFramerateLimit(60);
        std::cout << "GameManager created!" << std::endl;
    }

    ~GameManager() = default;

    void start_game()
    {
        createMainMenu();
        createPlayer();
        createBackground();
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
                    _input_manager.processInput(event);
                }
            }
            _window.clear();

            parallaxSystem(deltaTime.asSeconds());
            renderSystem();
            _window.display();
        }
    }

    void renderSystem()
    {
        debugPrintCurrentScene();
        _scene_manager.getCurrentSceneName();
        auto view = _registry.view<RenderableComponent, SceneComponent>();
        for (auto entity : view) {
            auto& sceneComponent = view.get<SceneComponent>(entity);
            // printf("Scene: %d\n", sceneComponent.scene.value_or(-1));
            if (sceneComponent.scene.has_value() &&
                sceneComponent.scene == _scene_manager.getCurrentScene()) {
                auto& renderable = view.get<RenderableComponent>(entity);

                if (renderable.text.getFont()) {
                    printf(
                        "Text: %s\n",
                        renderable.text.getString().toAnsiString().c_str()
                    );
                    _window.draw(renderable.text);
                }
                // if (renderable.sprite.getTexture()) {
                //     _window.draw(renderable.sprite);
                // }
            }
            if (!sceneComponent.scene.has_value()) {
                auto& renderable = view.get<RenderableComponent>(entity);
                _window.draw(renderable.sprite);
            }

            else {
                continue;
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

    // entt::entity createSpriteEntity(
    //     const std::string& texturePath, const sf::IntRect& frameRect,
    //     const sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f)
    // )
    // {
    //     auto texture = _resource_manager.loadTexture(texturePath);

    //     auto entity = _registry.create();
    //     RenderableComponent renderable;
    //     renderable.texture = texture;
    //     renderable.sprite.setTexture(*texture);
    //     renderable.sprite.setTextureRect(frameRect);
    //     renderable.sprite.setScale(scale);

    //     _registry.emplace<RenderableComponent>(entity, std::move(renderable));

    //     return entity;
    // }

    entt::entity createPlayer()
    {
        auto player = _registry.create();
        auto texture = _resource_manager.loadTexture(
            _assetsPath + "/Player/spaceship.gif"
        );
        sf::IntRect initialFrameRect(66, 0, 33, 17);

        auto entity = _registry.create();
        RenderableComponent renderable;
        renderable.texture = texture;
        renderable.sprite.setTexture(*texture);
        renderable.sprite.setScale(Vector2f(5.0, 5.0));
        renderable.frameRect = initialFrameRect;
        renderable.sprite.setTextureRect(initialFrameRect);

        _registry.emplace<RenderableComponent>(entity, std::move(renderable));

        _registry.emplace<TransformComponent>(
            player, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f
        );

        _registry.emplace<VelocityComponent>(player, 0.0f, 0.0f, 1.0f);

        _registry.emplace<WeaponComponent>(
            player, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100,
            false
        );

        _registry.emplace<ScoreComponent>(player, 0, 1.0f, 0);

        _registry.emplace<HealthComponent>(player, 100);

        return player;
    }

    entt::entity createBackground()
    {
        auto texture = _resource_manager.loadTexture(
            _assetsPath + "/Background/Layer 3/Space_background.png"
        );

        auto background = _registry.create();
        RenderableComponent renderable;
        renderable.texture = texture;
        renderable.sprite.setTexture(*texture);
        renderable.sprite.setPosition(Vector2f(0.0f, 0.0f));

        _registry.emplace<RenderableComponent>(
            background, std::move(renderable)
        );

        _registry.emplace<TransformComponent>(
            background, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f
        );
        _registry.emplace<ParallaxComponent>(background, 100.0f);
        _registry.emplace<SceneComponent>(background);

        return background;
    };

    entt::entity createMainMenu()
    {
        auto font =
            _resource_manager.loadFont(_assetsPath + "/fonts/francis.ttf");

        auto mainMenuTitle = _registry.create();
        RenderableComponent renderable;

        renderable.text.setFont(*font);

        renderable.text.setString("R-Type");
        renderable.text.setCharacterSize(96);
        sf::FloatRect titleBounds = renderable.text.getLocalBounds();
        renderable.text.setOrigin(
            titleBounds.width / 2, titleBounds.height / 2
        );
        renderable.text.setPosition(
            _window.getSize().x / 2, _window.getSize().y * 0.20
        );

        _registry.emplace<RenderableComponent>(
            mainMenuTitle, std::move(renderable)
        );
        _registry.emplace<SceneComponent>(mainMenuTitle, GameScenes::MainMenu);

        return mainMenuTitle;
    };

    void debugPrintCurrentScene() const
    {
        GameScenes currentScene = _scene_manager.getCurrentScene();
        std::string sceneName = getSceneName(currentScene);
        std::cout << "Current scene: " << sceneName << std::endl;
    };
};

#endif  // GAME_MANAGER_HPP