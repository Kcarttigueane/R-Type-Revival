#include "../../include/managers/game_manager.hpp"

void GameManager::moveSettingLine(int direction)
{
    auto view = _registry.view<SettingItemComponent>();

    int currentIndex = -1;
    int totalItems = static_cast<int>(view.size());
    std::vector<entt::entity> items(view.begin(), view.end());

    for (int i = 0; i < totalItems; ++i) {
        auto& settingItem = view.get<SettingItemComponent>(items[i]);
        if (settingItem.isSelected) {
            currentIndex = i;
            break;
        }
    }

    for (auto entity : view) {
        view.get<SettingItemComponent>(entity).isSelected = false;
    }

    if (currentIndex != -1) {
        int newIndex = (currentIndex + direction + totalItems) % totalItems;
        view.get<SettingItemComponent>(items[newIndex]).isSelected = true;
    }
}

void GameManager::updateSettingHighlight()
{
    auto view = _registry.view<SettingItemComponent, RenderableComponent>();

    for (auto entity : view) {
        auto& settingItem = view.get<SettingItemComponent>(entity);
        auto& renderable = view.get<RenderableComponent>(entity);

        if (settingItem.isSelected) {
            renderable.text.setFillColor(sf::Color::Red);
        } else {
            renderable.text.setFillColor(sf::Color::White);
        }
    }
}

void GameManager::settingsSystem(float deltaTime)
{
    if (menuMoveCooldown > 0) {
        menuMoveCooldown -= deltaTime;
    }

    auto view = _registry.view<SettingItemComponent, RenderableComponent>();

    auto keyboardActions = _inputManager.getKeyboardActions();

    if (menuMoveCooldown <= 0) {
        if (keyboardActions.Enter) {
            for (auto entity : view) {
                auto& settingItem = view.get<SettingItemComponent>(entity);
                auto& renderable = view.get<RenderableComponent>(entity);

                if (settingItem.isSelected) {
                    settingItem.currentValueIndex =
                        (settingItem.currentValueIndex + 1) %
                        settingItem.values.size();

                    renderable.text.setString(
                        settingItem.name + ": " +
                        settingItem.values[settingItem.currentValueIndex]
                    );

                    break;
                }
            }
            menuMoveCooldown = menuMoveDelay;
        } else if (keyboardActions.Up) {
            moveSettingLine(1);
            menuMoveCooldown = menuMoveDelay;
        } else if (keyboardActions.Down) {
            moveSettingLine(-1);
            menuMoveCooldown = menuMoveDelay;
        } else if (keyboardActions.Backspace) {
            _sceneManager.setCurrentScene(GameScenes::MainMenu);
            menuMoveCooldown = menuMoveDelay;
        }
    }

    updateSettingHighlight();
}
