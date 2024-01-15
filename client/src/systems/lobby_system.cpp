#include "../../include/managers/game_manager.hpp"

void GameManager::lobbySystem(float deltaTime)
{
    auto& keyboardActions = _inputManager.getKeyboardActions();

    if (menuMoveCooldown > 0) {
        menuMoveCooldown -= deltaTime;
    }

    size_t prevSelectedTitleIndex = selectedTitleIndex;

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
        // uint32_t port = static_cast<uint32_t>(std::stoi(
        //     _registry.get<RenderableComponent>(portEntity).text.getString().toAnsiString()
        // ));
        // std::string ip =
        //     _registry.get<RenderableComponent>(ipEntity).text.getString().toAnsiString();

        std::string playerName =
            _registry.get<RenderableComponent>(usernameEntity).text.getString().toAnsiString();

        rtype::Connect connect_message;
        connect_message.set_player_name(playerName);
        rtype::Payload payload;
        payload.mutable_connect()->CopyFrom(connect_message);
        _networkManager.send(payload);
        _sceneManager.setCurrentScene(GameScenes::InGame);
    } else if (keyboardActions.Escape && menuMoveCooldown <= 0) {
        _sceneManager.setCurrentScene(GameScenes::MainMenu);
    }

    updateSelectedTitle(prevSelectedTitleIndex);
    updateCurrentTitle();
    updateInputFieldText();
}

void GameManager::updateSelectedTitle(size_t prevSelectedTitleIndex)
{
    if (prevSelectedTitleIndex < titleEntities.size()) {
        auto& prevTitleTextComponent =
            _registry.get<RenderableComponent>(titleEntities[prevSelectedTitleIndex]);
        prevTitleTextComponent.text.setFillColor(sf::Color::White);
    }
}

void GameManager::updateCurrentTitle()
{
    selectedTitleIndex = selectedInputField;

    if (selectedTitleIndex < titleEntities.size()) {
        auto& titleTextComponent =
            _registry.get<RenderableComponent>(titleEntities[selectedTitleIndex]);
        titleTextComponent.text.setFillColor(sf::Color::Red);
    }
}

void GameManager::updateInputFieldText()
{
    auto& keyboardActions = _inputManager.getKeyboardActions();

    auto& textComponent = _registry.get<RenderableComponent>(inputFields[selectedInputField]).text;
    std::string currentText = textComponent.getString();

    std::string tempText = currentText;

    if (keyboardActions.Backspace == true && !tempText.empty()) {
        tempText.pop_back();
        keyboardActions.Backspace = false;
    } else if (!keyboardActions.TextInput.empty()) {
        tempText += keyboardActions.TextInput;
        keyboardActions.TextInput.clear();
    }
    textComponent.setString(tempText);
}
