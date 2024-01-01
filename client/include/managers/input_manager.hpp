#if !defined(INPUT_MANAGER_HPP)
#    define INPUT_MANAGER_HPP

// Managers
#    include "../config.hpp"

// Libraries
#    include <fmt/color.h>
#    include <fmt/core.h>
#    include <fmt/ranges.h>
#    include <queue>

#    include <SFML/Audio.hpp>
#    include <SFML/Graphics.hpp>
#    include <SFML/System.hpp>
#    include <SFML/Window.hpp>

#    include "../../../libs/EnTT/entt.hpp"

#    include <format>
#    include <functional>
#    include <iostream>
#    include <map>
#    include <set>
#    include <sstream>

#    include <queue>

#    include "../../../common/components/component_includes.hpp"

enum class PlayerAction {
    Shoot,
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    UsePowerUp,
};

class InputManager {
private:
    GameScenes _currentScene;
    entt::registry& _registry;
    sf::RenderWindow& _window;
    std::map<GameScenes, std::map<sf::Keyboard::Key, std::function<void()>>>
        _actionBindings;
    std::queue<PlayerAction> _playerActionsQueue;
    // std::map<sf::Mouse::Button, std::function<void()>> _mouseButtonBindings;
    // std::set<sf::Keyboard::Key> _heldKeys;

public:
    InputManager() = delete;

    InputManager(entt::registry& _registry, sf::RenderWindow& window)
        : _currentScene(GameScenes::MainMenu),
          _registry(_registry),
          _window(window)
    {
        initializeInGameBindings();
        initializeMainMenuBindings();
        initializeSettingsBindings();
        initializePauseMenuBindings();
        initializeGameOverBindings();
        initializeTutorialBindings();
        initializeQuitBindings();
    }

    ~InputManager() = default;

    [[nodiscard]] GameScenes getContext() const { return _currentScene; }

    void setContext(GameScenes context) { _currentScene = context; }

    [[nodiscard]] std::queue<PlayerAction>& getPlayerActionsQueue()
    {
        return _playerActionsQueue;
    }

    void initializeInGameBindings()
    {
        _actionBindings[GameScenes::InGame][sf::Keyboard::Space] = [this]() {
            _playerActionsQueue.push(PlayerAction::Shoot);
        };
        _actionBindings[GameScenes::InGame][sf::Keyboard::Left] = [this]() {
            _playerActionsQueue.push(PlayerAction::MoveLeft);
        };
        _actionBindings[GameScenes::InGame][sf::Keyboard::Right] = [this]() {
            _playerActionsQueue.push(PlayerAction::MoveRight);
        };
        _actionBindings[GameScenes::InGame][sf::Keyboard::Up] = [this]() {
            _playerActionsQueue.push(PlayerAction::MoveUp);
        };
        _actionBindings[GameScenes::InGame][sf::Keyboard::Down] = [this]() {
            _playerActionsQueue.push(PlayerAction::MoveDown);
        };
    }

    void initializeMainMenuBindings()

    {
        _actionBindings[GameScenes::MainMenu][sf::Keyboard::Escape] = [this]() {
            auto view = _registry.view<entt::entity>();

            for (auto entity : view) {
                _registry.destroy(entity);
            }
            exit(0);
        };

        _actionBindings[GameScenes::MainMenu][sf::Keyboard::Enter] = [this]() {
            // TODO: Call function to go to a new scene
            std::cout << "[GameScenes::MainMenu] [sf::Keyboard::Enter] pressed!"
                      << std::endl;
        };

        _actionBindings[GameScenes::MainMenu][sf::Keyboard::Left] = [this]() {
            // TODO: Call function to go to left item in the menu list
            std::cout << "[GameScenes::MainMenu] [sf::Keyboard::Left] pressed!"
                      << std::endl;
        };

        _actionBindings[GameScenes::MainMenu][sf::Keyboard::Right] = [this]() {
            // TODO: Call function to go to the right item in the menu list
            std::cout << "[GameScenes::MainMenu] [sf::Keyboard::Right] pressed!"
                      << std::endl;
        };
    }

    void initializeSettingsBindings();
    void initializePauseMenuBindings();
    void initializeGameOverBindings();
    void initializeTutorialBindings();
    void initializeQuitBindings();

    void debugPrintBindings();

    std::string getContextName(GameScenes context);
    std::string getKeyName(sf::Keyboard::Key key);

    void processInput(sf::Event& event)
    {
        auto& action = _actionBindings[_currentScene][event.key.code];
        if (action) {
            action();
        }
    }
};

#endif  // INPUT_MANAGER_HPP
