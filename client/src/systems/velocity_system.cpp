#include "../../include/managers/game_manager.hpp"

void GameManager::velocitySystem()
{
    entt::basic_view entities =
        _registry.view<RenderableComponent, TransformComponent, VelocityComponent>();
    for (auto& entity : entities) {
        TransformComponent& transformable = _registry.get<TransformComponent>(entity);
        RenderableComponent& renderable = _registry.get<RenderableComponent>(entity);
        VelocityComponent& velocity = _registry.get<VelocityComponent>(entity);
        transformable.x = transformable.x + velocity.dx * velocity.speed;
        transformable.y = transformable.y + velocity.dy * velocity.speed;
        renderable.sprite.setPosition(sf::Vector2f(transformable.x, transformable.y));
        renderable.text.setPosition(sf::Vector2f(transformable.x, transformable.y));
        if (transformable.x > WINDOW_WIDTH + 1000.0f || transformable.x < -1000.0f ||
            transformable.y > WINDOW_HEIGHT + 1000.0f || transformable.y < -1000.0f) {
            _registry.destroy(entity);
            printf("Entity out of bound destroyed\n");
        }
    }
}