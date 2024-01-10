#if !defined(INPUT_MANAGER_HPP)
#    define INPUT_MANAGER_HPP

// Managers
#    include "../config.hpp"

// Libraries
#    include <queue>

#    include <SFML/Audio.hpp>
#    include <SFML/Graphics.hpp>
#    include <SFML/System.hpp>
#    include <SFML/Window.hpp>

#    include "../../../libs/EnTT/entt.hpp"

// #    include <format>
#    include <functional>
#    include <iostream>
#    include <map>
#    include <set>
#    include <sstream>

#    include <queue>

#    include "../../../common/components/component_includes.hpp"

struct Actions {
    bool Spacebar;
    bool Up;
    bool Down;
    bool Right;
    bool Left;
    bool Enter;
    bool Backspace;
};

class InputManager {
private:
    GameScenes _currentScene;
    entt::registry& _registry;
    sf::RenderWindow& _window;
    Actions keyboardActions;

public:
    InputManager() = delete;

    InputManager(entt::registry& _registry, sf::RenderWindow& window)
        : _currentScene(GameScenes::InGame),
          _registry(_registry),
          _window(window)
    {}

    ~InputManager() = default;

    [[nodiscard]] GameScenes getContext() const { return _currentScene; }

    void setContext(GameScenes context) { _currentScene = context; }

    [[nodiscard]] Actions& getKeyboardActions() { return keyboardActions; }

    void processKeyPress(sf::Event& event)
    {
        if (event.type == event.KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                keyboardActions.Left = true;
            }
            if (event.key.code == sf::Keyboard::Right) {
                keyboardActions.Right = true;
            }
            if (event.key.code == sf::Keyboard::Up) {
                keyboardActions.Up = true;
            }
            if (event.key.code == sf::Keyboard::Down) {
                keyboardActions.Down = true;
            }
            if (event.key.code == sf::Keyboard::Enter) {
                keyboardActions.Enter = true;
            }
            if (event.key.code == sf::Keyboard::Backspace) {
                keyboardActions.Backspace = true;
            }
        }
    }

    void processKeyRelease(sf::Event& event)
    {
        if (event.type == event.KeyReleased) {
            if (event.key.code == sf::Keyboard::Left) {
                keyboardActions.Left = false;
            }
            if (event.key.code == sf::Keyboard::Right) {
                keyboardActions.Right = false;
            }
            if (event.key.code == sf::Keyboard::Up) {
                keyboardActions.Up = false;
            }
            if (event.key.code == sf::Keyboard::Down) {
                keyboardActions.Down = false;
            }
            if (event.key.code == sf::Keyboard::Enter) {
                keyboardActions.Enter = false;
            }
            if (event.key.code == sf::Keyboard::Backspace) {
                keyboardActions.Backspace = false;
            }
        }
    }
};

#endif  // INPUT_MANAGER_HPP
