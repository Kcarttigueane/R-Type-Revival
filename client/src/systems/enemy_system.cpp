#include "../../include/managers/game_manager.hpp"

void GameManager::enemySystem(sf::Sound& explosionSound)
{
    auto enemies = _registry.view<
        EnemyAIComponent, RenderableComponent, VelocityComponent, HealthComponent,
        TransformComponent, SoundComponent>();
    std::vector<entt::entity> entitiesToDestroy;

    for (auto& entity : enemies) {
        auto& enemy = enemies.get<RenderableComponent>(entity);
        auto& velocity = enemies.get<VelocityComponent>(entity);
        auto& position = enemies.get<TransformComponent>(entity);
        float& health = enemies.get<HealthComponent>(entity).healthPoints;

        sf::Vector2f enemyPosition = enemy.sprite.getPosition();

        if (health <= 0.0f) {
            explosionSound.play();
            entitiesToDestroy.push_back(entity);
            _entityFactory.createExplosion(
                enemy.sprite.getPosition().x - 200, enemy.sprite.getPosition().y - 60
            );
        }
        if (enemyPosition.x < -128.0f) {
            entitiesToDestroy.push_back(entity);
        } else {
            position.x = enemyPosition.x + velocity.dx * velocity.speed;
            position.y = enemyPosition.y + velocity.dy * velocity.speed;
        }
    }

    for (auto entity : entitiesToDestroy) {
        _registry.destroy(entity);
    }
}
