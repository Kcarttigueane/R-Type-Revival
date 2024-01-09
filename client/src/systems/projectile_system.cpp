#include "../../include/managers/game_manager.hpp"

void GameManager::projectileSystem()
{
    auto projectiles =
        _registry.view<RenderableComponent, DamageComponent, VelocityComponent, TransformComponent>(
        );

    std::vector<entt::entity> entitiesToDestroy;

    for (auto& entity : projectiles) {
        auto& projectile = projectiles.get<RenderableComponent>(entity);
        auto& velocity = projectiles.get<VelocityComponent>(entity);
        auto& postion = projectiles.get<TransformComponent>(entity);
        sf::Vector2f projectilePosition = projectile.sprite.getPosition();

        if (projectilePosition.x > WINDOW_WIDTH || projectilePosition.x < -64.0f) {
            entitiesToDestroy.push_back(entity);
        } else {
            postion.x = projectilePosition.x + velocity.dx * velocity.speed;
            postion.y = projectilePosition.y + velocity.dy * velocity.speed;
        };
    }

    for (auto entity : entitiesToDestroy) {
        _registry.destroy(entity);
        printf("Projectile Deleted\n");
    }
}
