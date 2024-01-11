#include "../../include/managers/game_manager.hpp"

void GameManager::velocitySystem()
{
    entt::registry& registry = _entity_manager.getRegistry();
    entt::basic_view entities = registry.view<TransformComponent, VelocityComponent>();
    for (auto &entity : entities) {
        TransformComponent &transformable = registry.get<TransformComponent>(entity);
        VelocityComponent &velocity = registry.get<VelocityComponent>(entity);
        transformable.x = transformable.x + velocity.dx * velocity.speed;
        transformable.y = transformable.y + velocity.dy * velocity.speed;
        if (transformable.x > WINDOW_WIDTH + 1000.0f || transformable.x < -1000.0f ||
        transformable.y > WINDOW_HEIGHT + 1000.0f || transformable.y <- 1000.0f) {
            registry.destroy(entity);
            printf("Entity out of bound destroyed\n");
        }
    }
}