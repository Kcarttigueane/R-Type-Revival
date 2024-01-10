#include "../../include/managers/scene_manager.hpp"

[[nodiscard]] GameScenes SceneManager::getCurrentScene() const
{
    return _current_scene;
}

void SceneManager::setCurrentScene(GameScenes scene)
{
    _current_scene = scene;
}

void SceneManager::getCurrentSceneName() const
{
    switch (_current_scene) {
        case GameScenes::MainMenu:
            std::cout << "MainMenu" << std::endl;
            break;
        case GameScenes::InGame:
            std::cout << "InGame" << std::endl;
            break;
        case GameScenes::GameOver:
            std::cout << "GameOver" << std::endl;
            break;
        case GameScenes::Settings:
            std::cout << "Settings" << std::endl;
            break;
        case GameScenes::Tutorial:
            std::cout << "Credits" << std::endl;
            break;
        case GameScenes::Quit:
            std::cout << "Quit" << std::endl;
            break;
        case GameScenes::PauseMenu:
            std::cout << "PauseMenu" << std::endl;
            break;
        case GameScenes::Lose:
            std::cout << "Lose" << std::endl;
            break;
        case GameScenes::Win:
            std::cout << "Win" << std::endl;
            break;
        default:
            std::cout << "Unknown" << std::endl;
            break;
    }
}
