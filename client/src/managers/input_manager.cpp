#include "../../include/managers/input_manager.hpp"

void InputManager::initializeSettingsBindings()
{
    _actionBindings[GameScenes::Settings][sf::Keyboard::Escape] = [this]() {
        // TODO: Call function to go to a new scene -> should go back to the main menu
        std::cout << "[GameScenes::Settings] [Escape] pressed!" << std::endl;
    };
}

void InputManager::initializePauseMenuBindings()
{
    _actionBindings[GameScenes::PauseMenu][sf::Keyboard::Escape] = [this]() {
        // TODO: Call function to go to a new scene -> should go back to the game
        std::cout << "[GameScenes::PauseMenu] [Escape] pressed!" << std::endl;
    };
}

void InputManager::initializeGameOverBindings()
{
    _actionBindings[GameScenes::GameOver][sf::Keyboard::Escape] = [this]() {
        // TODO: Call function to go to a new scene -> should go back to the main menu
        std::cout << "[GameScenes::GameOver] [Escape] pressed!" << std::endl;
    };
}

void InputManager::initializeTutorialBindings()
{
    _actionBindings[GameScenes::Tutorial][sf::Keyboard::Escape] = [this]() {
        // TODO: Call function to go to a new scene -> should go back to the main menu
        std::cout << "[GameScenes::Tutorial] [Escape] pressed!" << std::endl;
    };
}

void InputManager::initializeQuitBindings()
{
    _actionBindings[GameScenes::Quit][sf::Keyboard::Escape] = [this]() {
        // TODO: Call function to go to a new scene -> should go back to the main menu
        std::cout << "[GameScenes::Quit] [Escape] pressed!" << std::endl;
    };
}

void InputManager::debugPrintBindings()
{
    std::ostringstream stream;

    stream << "Debugging Input Bindings:\n";

    for (const auto& [context, bindings] : _actionBindings) {
        std::string contextName = getContextName(context);
        stream << std::format("Context: {}\n", contextName);

        for (const auto& [key, action] : bindings) {
            std::string keyName = getKeyName(key);
            stream << std::format("  Key: {}\n", keyName);
        }
    }

    std::cout << stream.str();
}

std::string InputManager::getContextName(GameScenes context)
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
        case GameScenes::Tutorial:
            return "Tutorial";
        default:
            return "Unknown";
    }
}

std::string InputManager::getKeyName(sf::Keyboard::Key key)
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
