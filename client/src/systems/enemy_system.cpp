#include "../../include/managers/game_manager.hpp"
#include "../../include/utils.hpp"

void GameManager::enemySystem(sf::Sound& explosionSound)
{
    entt::basic_view enemies = _registry.view<EnemyAIComponent, TransformComponent, HealthComponent>();
    for (auto& entity : enemies) {
        float& health = enemies.get<HealthComponent>(entity).healthPoints;
        TransformComponent& transformable = enemies.get<TransformComponent>(entity);
        if (health <= 0.0f) {
            explosionSound.play();
            _score++;
            _entityFactory.createExplosion(
                transformable.x - 200, transformable.y - 60
            );
            _registry.destroy(entity);
            printf("Enemy killed\n");
        }
    }
}

void GameManager::makeEnemyShoot()
{
    entt::basic_view shootingEnemies = _registry.view<EnemyAIComponent, WeaponComponent, TransformComponent>();
    for (auto& enemy : shootingEnemies) {
        float enemyX = shootingEnemies.get<TransformComponent>(enemy).x;
        float enemyY = shootingEnemies.get<TransformComponent>(enemy).y;
        float playerX = _registry.get<TransformComponent>(_playerProfileManager.getPlayerEntity()).x;
        float playerY = _registry.get<TransformComponent>(_playerProfileManager.getPlayerEntity()).y;
        std::pair<float, float> direction = get_direction(enemyX, enemyY, playerX, playerY);
        _entityFactory.createEnemyProjectile(direction.first, direction.second, enemyX, enemyY, 5.0f);
    }
}
