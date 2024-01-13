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
            break;
        case GameScenes::InGame:
            break;
        case GameScenes::GameOver:
            break;
        case GameScenes::Settings:
            break;
        case GameScenes::Tutorial:
            break;
        case GameScenes::Quit:
            break;
        case GameScenes::PauseMenu:
            break;
        case GameScenes::Lose:
            break;
        case GameScenes::Win:
            break;
        default:
            break;
    }
}
