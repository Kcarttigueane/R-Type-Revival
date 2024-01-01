#include "../../include/managers/game_manager.hpp"

void GameManager::enemySystem()
{
    auto enemies = _registry.view<
        EnemyAIComponent, RenderableComponent, VelocityComponent,
        HealthComponent, TransformComponent>();
    std::vector<entt::entity> entitiesToDestroy;
    for (auto& entity : enemies) {
        auto& enemy = enemies.get<RenderableComponent>(entity);
        auto& velocity = enemies.get<VelocityComponent>(entity);
        auto& postion = enemies.get<TransformComponent>(entity);
        float& health = enemies.get<HealthComponent>(entity).healthPoints;
        sf::Vector2f enemyPosition = enemy.sprite.getPosition();

        if (enemyPosition.x < -128.0f || health <= 0.0f) {
            entitiesToDestroy.push_back(entity);
        } else {
            postion.x = enemyPosition.x + velocity.dx * velocity.speed;
            postion.y = enemyPosition.y + velocity.dy * velocity.speed;
        }
    }
    for (auto entity : entitiesToDestroy) {
        _registry.destroy(entity);
        printf("Entity Deleted\n");
    }
}