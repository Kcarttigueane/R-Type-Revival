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
        if (event.key.code == sf::Keyboard::Enter) {
            keyboardActions.Enter = true;
        }
        if (event.key.code == sf::Keyboard::BackSpace) {
            keyboardActions.Backspace = true;
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
        if (event.key.code == sf::Keyboard::Enter) {
            keyboardActions.Enter = false;
        }
        if (event.key.code == sf::Keyboard::BackSpace) {
            keyboardActions.Backspace = false;
        }
    }
}

void InputManager::processTextInput(sf::Event& event)
{
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 32 && event.text.unicode < 128) {
            keyboardActions.TextInput += static_cast<char>(event.text.unicode);
        }
    }
}

void InputManager::clearTextInput()
{
    keyboardActions.TextInput.clear();
}
