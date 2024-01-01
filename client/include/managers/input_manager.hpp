#if !defined(INPUT_MANAGER_HPP)
#    define INPUT_MANAGER_HPP

// Managers
#    include "../config.hpp"

// Libraries
#    include <fmt/color.h>
#    include <fmt/core.h>
#    include <fmt/ranges.h>
#    include <queue>

#    include <SFML/Window/Keyboard.hpp>
#    include <SFML/Window/Mouse.hpp>
#    include <format>
#    include <functional>
#    include <iostream>
#    include <map>
#    include <set>

class InputManager {
private:
    GameScenes _currentScene;
    std::map<GameScenes, std::map<sf::Keyboard::Key, std::function<void()>>>
        _actionBindings;
    // std::queue<PlayerAction> _playerActionsQueue;

    // std::map<sf::Mouse::Button, std::function<void()>> _mouseButtonBindings;
    // std::set<sf::Keyboard::Key> _heldKeys;

public:
    InputManager() : _currentScene(GameScenes::MainMenu)
    {
        initializeInGameBindings();
        initializeMainMenuBindings();
        initializeSettingsBindings();
        initializePauseMenuBindings();
        initializeGameOverBindings();
        initializeCreditsBindings();
        initializeQuitBindings();
    }

    ~InputManager() = default;

    [[nodiscard]] GameScenes getContext() const { return _currentScene; }

    void setContext(GameScenes context) { _currentScene = context; }

    void initializeInGameBindings()
    {
        _actionBindings[GameScenes::InGame][sf::Keyboard::Space] = [this]() {
            // TODO: Call function to shoot
            std::cout << "[GameScenes::InGame] [sf::Keyboard::Space] pressed!"
                      << std::endl;
            // _playerActionsQueue.push(PlayerAction::Shoot);
        };

        _actionBindings[GameScenes::InGame][sf::Keyboard::Left] = [this]() {
            // TODO: Call function to go to a new scene
            std::cout << "[GameScenes::InGame] [sf::Keyboard::Left] pressed!"
                      << std::endl;
        };

        _actionBindings[GameScenes::InGame][sf::Keyboard::Right] = [this]() {
            // TODO: Call function to go to a new scene
            std::cout << "[GameScenes::InGame] [sf::Keyboard::Right] pressed!"
                      << std::endl;
        };
        _actionBindings[GameScenes::InGame][sf::Keyboard::Up] = [this]() {
            // TODO: Call function to go to a new scene
            std::cout << "[GameScenes::InGame] [sf::Keyboard::Up] pressed!"
                      << std::endl;
        };

        _actionBindings[GameScenes::InGame][sf::Keyboard::Down] = [this]() {
            // TODO: Call function to go to a new scene
            std::cout << "[GameScenes::InGame] [sf::Keyboard::Down] pressed!"
                      << std::endl;
        };
    }

    void initializeMainMenuBindings()
    {
        _actionBindings[GameScenes::MainMenu][sf::Keyboard::Escape] = [this]() {
            // TODO: Call function to go to a new scene -> quit the game
            std::cout
                << "[GameScenes::MainMenu] [sf::Keyboard::Escape] pressed!"
                << std::endl;
        };

        _actionBindings[GameScenes::MainMenu][sf::Keyboard::Enter] = [this]() {
            // TODO: Call function to go to a new scene
            std::cout << "[GameScenes::MainMenu] [sf::Keyboard::Enter] pressed!"
                      << std::endl;
        };
        _actionBindings[GameScenes::MainMenu][sf::Keyboard::Left] = [this]() {
            // TODO: Call function to go to a new scene
            std::cout << "[GameScenes::MainMenu] [sf::Keyboard::Left] pressed!"
                      << std::endl;
        };

        _actionBindings[GameScenes::MainMenu][sf::Keyboard::Right] = [this]() {
            // TODO: Call function to go to a new scene
            std::cout << "[GameScenes::MainMenu] [sf::Keyboard::Right] pressed!"
                      << std::endl;
        };
    }

    void initializeSettingsBindings()
    {
        _actionBindings[GameScenes::Settings][sf::Keyboard::Escape] = [this]() {
            // TODO: Call function to go to a new scene -> should go back to the main menu
            std::cout
                << "[GameScenes::Settings] [sf::Keyboard::Escape] pressed!"
                << std::endl;
        };
    }

    void initializePauseMenuBindings()
    {
        _actionBindings[GameScenes::PauseMenu][sf::Keyboard::Escape] =
            [this]() {
                // TODO: Call function to go to a new scene -> should go back to the game
                std::cout
                    << "[GameScenes::PauseMenu] [sf::Keyboard::Escape] pressed!"
                    << std::endl;
            };
    }

    void initializeGameOverBindings()
    {
        _actionBindings[GameScenes::GameOver][sf::Keyboard::Escape] = [this]() {
            // TODO: Call function to go to a new scene -> should go back to the main menu
            std::cout
                << "[GameScenes::GameOver] [sf::Keyboard::Escape] pressed!"
                << std::endl;
        };
    }

    void initializeCreditsBindings()
    {
        _actionBindings[GameScenes::Credits][sf::Keyboard::Escape] = [this]() {
            // TODO: Call function to go to a new scene -> should go back to the main menu
            std::cout << "[GameScenes::Credits] [sf::Keyboard::Escape] pressed!"
                      << std::endl;
        };
    }

    void initializeQuitBindings()
    {
        _actionBindings[GameScenes::Quit][sf::Keyboard::Escape] = [this]() {
            // TODO: Call function to go to a new scene -> should go back to the main menu
            std::cout << "[GameScenes::Quit] [sf::Keyboard::Escape] pressed!"
                      << std::endl;
        };
    }

    void debugPrintBindings()
    {
        fmt::print(fmt::fg(fmt::color::green), "Debugging Input Bindings:\n");

        for (const auto& [context, bindings] : _actionBindings) {
            std::string contextName = getContextName(context);
            fmt::print(
                fmt::fg(fmt::color::yellow), "Context: {}\n", contextName
            );

            for (const auto& [key, action] : bindings) {
                std::string keyName = getKeyName(key);
                fmt::print(fmt::fg(fmt::color::cyan), "  Key: {}\n", keyName);
            }
        }
    }

    static std::string getContextName(GameScenes context)
    {
        switch (context) {
            case GameScenes::InGame:
                return "InGame";
            case GameScenes::MainMenu:
                return "MainMenu";
            case GameScenes::PauseMenu:
                return "PauseMenu";
            case GameScenes::Quit:
                return "Quit";
            case GameScenes::Settings:
                return "Settings";
            case GameScenes::GameOver:
                return "GameOver";
            case GameScenes::Credits:
                return "Credits";
            default:
                return "Unknown";
        }
    }

    static std::string getKeyName(sf::Keyboard::Key key)
    {
        switch (key) {
            case sf::Keyboard::Space:
                return "Space";
            case sf::Keyboard::Enter:
                return "Enter";
            // TODO -> Ajouter les autres cas quand vous en avez besoin les gars
            default:
                return "Unknown";
        }
    }

    void processInput(sf::Event& event)
    {
        auto& action = _actionBindings[_currentScene][event.key.code];
        if (action) {
            action();
        }
    }
};

#endif  // INPUT_MANAGER_HPP
