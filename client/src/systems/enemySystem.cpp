#include "../../include/managers/game_manager.hpp"

void GameManager::enemySystem()
{
    auto enemies =
        _registry
            .view<EnemyAIComponent, RenderableComponent, VelocityComponent>();
    std::vector<entt::entity> entitiesToDestroy;
    for (auto& entity : enemies) {
        auto& enemy = enemies.get<RenderableComponent>(entity);
        auto& velocity = enemies.get<VelocityComponent>(entity);
        sf::Vector2f enemyPosition = enemy.sprite.getPosition();

        if (enemyPosition.x < -128.0f) {
            entitiesToDestroy.push_back(entity);
        } else {
            enemy.sprite.setPosition(sf::Vector2f(
                enemyPosition.x + velocity.x * velocity.speed,
                enemyPosition.y + velocity.y * velocity.speed
            ));
        }
    }
    for (auto entity : entitiesToDestroy) {
        _registry.destroy(entity);
        printf("Entity Deleted\n");
    }
}
