#include "../../include/managers/scene_manager.hpp"

SceneManager::SceneManager(InputManager& input_manager) : _inputManager(input_manager) {}

[[nodiscard]] GameScenes SceneManager::getCurrentScene() const
{
    return _current_scene;
}

void SceneManager::setCurrentScene(GameScenes scene)
{
    _current_scene = scene;
}
