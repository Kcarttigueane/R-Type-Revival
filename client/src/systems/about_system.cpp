#include "../../include/managers/game_manager.hpp"

void GameManager::aboutSystem() {

    auto keyboardActions = _inputManager.getKeyboardActions();

    if (keyboardActions.Escape) {
        _sceneManager.setCurrentScene(GameScenes::MainMenu);
    }
}
