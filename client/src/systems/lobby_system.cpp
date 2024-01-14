#include "../../include/managers/game_manager.hpp"

void GameManager::lobbySystem(float deltaTime)
{
    auto& keyboardActions = _inputManager.getKeyboardActions();

    if (menuMoveCooldown > 0) {
        menuMoveCooldown -= deltaTime;
    }

    if (keyboardActions.Down && selectedInputField < inputFields.size() - 1 &&
        menuMoveCooldown <= 0) {
        selectedInputField++;
        keyboardActions.Down = false;
        menuMoveCooldown = menuMoveDelay;
    } else if (keyboardActions.Up && selectedInputField > 0 && menuMoveCooldown <= 0) {
        selectedInputField--;
        keyboardActions.Up = false;
        menuMoveCooldown = menuMoveDelay;
    } else if (keyboardActions.Enter && menuMoveCooldown <= 0) {
        _sceneManager.setCurrentScene(GameScenes::InGame);
    }

    auto& textComponent = _registry.get<RenderableComponent>(inputFields[selectedInputField]).text;
    std::string currentText = textComponent.getString();

    int minLength = 0;

    std::string tempText = currentText;

    if (keyboardActions.Backspace && !tempText.empty()) {
        std::cout << "Before Backspace: " << tempText << std::endl;
        tempText.pop_back();
        std::cout << "After Backspace: " << tempText << std::endl;
        keyboardActions.Backspace = false;
    } else if (!keyboardActions.TextInput.empty()) {
        tempText += keyboardActions.TextInput;
        keyboardActions.TextInput.clear();
    }
    textComponent.setString(tempText);
}
