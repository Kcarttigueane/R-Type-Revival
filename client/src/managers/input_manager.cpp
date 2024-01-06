#include "../../include/managers/input_manager.hpp"

[[nodiscard]] GameScenes InputManager::getContext() const
{
    return _currentScene;
}

void InputManager::setContext(GameScenes context)
{
    _currentScene = context;
}

[[nodiscard]] Actions& InputManager::getKeyboardActions()
{
    return keyboardActions;
}

void InputManager::processKeyPress(sf::Event& event)
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
    }
}

void InputManager::processKeyRelease(sf::Event& event)
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
    }
}
