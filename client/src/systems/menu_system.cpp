#include "../../include/managers/game_manager.hpp"

void GameManager::menuSystem()
{
    auto view = _registry.view<MenuItemComponent, RenderableComponent>();

    for (auto entity : view) {
        auto& menuItem = view.get<MenuItemComponent>(entity);
        auto& renderable = view.get<RenderableComponent>(entity);

        // Adjust the position based on the index
        // You can use similar logic to positionMenuButtons
        // ...

        // Handle selection logic
        // Set menuItem.isSelected based on user input
        // ...x

        // Update sprite appearance based on selection
        if (menuItem.isSelected) {
            // Change appearance for selected item
        } else {
            // Default appearance
        }
    }
}
