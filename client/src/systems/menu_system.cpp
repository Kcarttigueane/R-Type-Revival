#include "../../include/managers/game_manager.hpp"

float GameManager::calculateButtonXPosition(int index)
{
    float buttonWidth = 310.0f * 0.4f;
    float buttonSpacing = 75.0f;
    int totalButtons = 5;
    float totalWidth =
        totalButtons * buttonWidth + (totalButtons - 1) * buttonSpacing;
    float firstButtonX =
        _window.getSize().x / 2.0f - totalWidth / 2.0f + buttonWidth / 2.0f;
    return firstButtonX + index * (buttonWidth + buttonSpacing);
}

void GameManager::moveMenuItems(int direction)
{
    auto view = _registry.view<MenuItemComponent, RenderableComponent>();
    std::vector<entt::entity> items(view.begin(), view.end());

    std::sort(
        items.begin(), items.end(),
        [this](entt::entity a, entt::entity b) {
            return _registry.get<MenuItemComponent>(a).index <
                   _registry.get<MenuItemComponent>(b).index;
        }
    );

    if (direction == -1) {
        auto leftmostItem = items.front();
        items.erase(items.begin());
        items.push_back(leftmostItem);
    } else if (direction == 1) {
        auto rightmostItem = items.back();
        items.pop_back();
        items.insert(items.begin(), rightmostItem);
    }

    for (int i = 0; i < items.size(); ++i) {
        auto& menuItem = _registry.get<MenuItemComponent>(items[i]);
        menuItem.index = i;

        float buttonX = calculateButtonXPosition(i);
        auto& transform = _registry.get<TransformComponent>(items[i]);
        transform.x = buttonX;

        menuItem.isSelected = (i == 2);
    }
}

void GameManager::changeGameState(const std::string& label)
{
    if (label == "Play") {
        std::cout << "Play" << std::endl;
        _sceneManager.setCurrentScene(GameScenes::InGame);
    } else if (label == "Settings") {
        std::cout << "Settings" << std::endl;
        _sceneManager.setCurrentScene(GameScenes::Settings);
    } else if (label == "Tutorial") {
        std::cout << "Tutorial" << std::endl;
        _sceneManager.setCurrentScene(GameScenes::Tutorial);
    } else if (label == "About") {
        std::cout << "About" << std::endl;
        _sceneManager.setCurrentScene(GameScenes::About);
    } else if (label == "Quit") {
        std::cout << "Quit" << std::endl;
        _sceneManager.setCurrentScene(GameScenes::Quit);
    }
}

void GameManager::menuSystem(float deltaTime)
{
    if (menuMoveCooldown > 0) {
        menuMoveCooldown -= deltaTime;
    }

    auto view = _registry.view<MenuItemComponent>();

    auto keyboardActions = _inputManager.getKeyboardActions();

    if (keyboardActions.Enter) {
        for (auto entity : view) {
            auto& menuItem = view.get<MenuItemComponent>(entity);
            if (menuItem.isSelected) {
                changeGameState(menuItem.label);
                break;
            }
        }
    }

    if (menuMoveCooldown <= 0) {
        if (keyboardActions.Left) {
            moveMenuItems(1);
            menuMoveCooldown = menuMoveDelay;
        } else if (keyboardActions.Right) {
            moveMenuItems(-1);
            menuMoveCooldown = menuMoveDelay;
        }
    }
}
