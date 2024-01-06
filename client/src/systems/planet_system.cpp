#include "../../include/managers/game_manager.hpp"

void GameManager::planetSystem(float deltaTime)
{
    auto view = _registry.view<PlanetComponent, RenderableComponent, TransformComponent>();

    for (auto entity : view) {
        auto& renderable = view.get<RenderableComponent>(entity);
        auto& transform = view.get<TransformComponent>(entity);
        renderable.sprite.setPosition(sf::Vector2f(transform.x, transform.y));
    }
};
