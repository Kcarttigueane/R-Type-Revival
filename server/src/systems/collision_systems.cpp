#include "../../include/managers/game_manager.hpp"

bool checkCollition(std::pair<float, float> collider, std::pair<float, float> collided,
    std::pair<float, float> colliderPosition, std::pair<float, float> collidedPosition) 
{
    float colliderHalfWidth = collider.first / 2.0f;
    float colliderHalfHeight = collider.second / 2.0f;

    float collidedHalfWidth = collided.first / 2.0f;
    float collidedHalfHeight = collided.second / 2.0f;

    float colliderLeft = colliderPosition.first - colliderHalfWidth;
    float colliderRight = colliderPosition.first + colliderHalfWidth;
    float colliderTop = colliderPosition.second - colliderHalfHeight;
    float colliderBottom = colliderPosition.second + colliderHalfHeight;

    float collidedLeft = collidedPosition.first - collidedHalfWidth;
    float collidedRight = collidedPosition.first + collidedHalfWidth;
    float collidedTop = collidedPosition.second - collidedHalfHeight;
    float collidedBottom = collidedPosition.second + collidedHalfHeight;

    if (colliderRight >= collidedLeft && colliderLeft <= collidedRight &&
    colliderBottom >= collidedTop && colliderTop <= collidedBottom) {
        return true;
    } else {
        return false;
    }
}

void GameManager::collisionProjectileAndEnemy()
{
    entt::registry& registry = _entity_manager.getRegistry();
    auto enemies = registry.view<EnemyComponent, HealthComponent, TransformComponent>();
    auto projectiles = registry.view<DamageComponent, TransformComponent, BulletTypeComponent, OwnerComponent>();

    for (auto& enemy : enemies) {
        TransformComponent& enemyTransform = enemies.get<TransformComponent>(enemy);
        float& enemyHealth = enemies.get<HealthComponent>(enemy).healthPoints;
        EnemyType enemyType = enemies.get<EnemyComponent>(enemy).type;

        for (auto& projectile : projectiles) {
            BulletTypeComponent& projectileType =
                projectiles.get<BulletTypeComponent>(projectile);
            if (projectileType.type == EntityType::PLAYER) {
                entt::entity player = static_cast<entt::entity>(projectiles.get<OwnerComponent>(projectile).id);
                int& playerScore = registry.get<ScoreComponent>(player).score;
                TransformComponent& projectileTransform =
                    projectiles.get<TransformComponent>(projectile);
                DamageComponent& projectileDamage = 
                    projectiles.get<DamageComponent>(projectile);
                if (enemyType == EnemyType::FAST && checkCollition(std::pair(projectileTransform.width * projectileTransform.scaleX, projectileTransform.height * projectileTransform.scaleY),
                std::pair(enemyTransform.height * enemyTransform.scaleY, enemyTransform.width * enemyTransform.scaleX), std::pair(projectileTransform.x, projectileTransform.y),
                std::pair(enemyTransform.x, enemyTransform.y))) {
                    playerScore += 50;
                    enemyHealth -= projectileDamage.damage;
                    registry.destroy(projectile);
                }
                if (enemyType == EnemyType::NORMAL && checkCollition(std::pair(projectileTransform.width * projectileTransform.scaleX, projectileTransform.height * projectileTransform.scaleY),
                std::pair(enemyTransform.width * enemyTransform.scaleX, enemyTransform.height * enemyTransform.scaleY), std::pair(projectileTransform.x, projectileTransform.y),
                std::pair(enemyTransform.x, enemyTransform.y))) {
                    playerScore += 10;
                    enemyHealth -= projectileDamage.damage;
                    registry.destroy(projectile);
                }
            }
        }
    }
}

void GameManager::collisionPlayerAndEnemy()
{
    entt::registry& registry = _entity_manager.getRegistry();
    auto players = registry.view<PlayerComponent, TransformComponent, HealthComponent>();
    auto enemies = registry.view<EnemyComponent, DamageComponent, TransformComponent>();

    for (auto& player : players) {
        TransformComponent& playerTransform = players.get<TransformComponent>(player);
        float& playerHealth = players.get<HealthComponent>(player).healthPoints;

        for (auto& enemy : enemies) {
            TransformComponent& enemyTransform =
                enemies.get<TransformComponent>(enemy);
            DamageComponent& enemyDamage = 
                enemies.get<DamageComponent>(enemy);
            if (checkCollition(std::pair(playerTransform.width * playerTransform.scaleX, playerTransform.height * playerTransform.scaleY),
            std::pair(enemyTransform.height * enemyTransform.scaleY, enemyTransform.width * enemyTransform.scaleX), std::pair(playerTransform.x, playerTransform.y),
            std::pair(enemyTransform.x, enemyTransform.y))) {
                playerHealth -= enemyDamage.damage;
            }
        }
    }
}

void GameManager::collisionPlayerAndEnemyBullet()
{
    entt::registry& registry = _entity_manager.getRegistry();
    auto players = registry.view<PlayerComponent, TransformComponent, HealthComponent>();
    auto bullets = registry.view<BulletTypeComponent, DamageComponent, TransformComponent>();

    for (auto& player : players) {
        TransformComponent& playerTransform = players.get<TransformComponent>(player);
        float& playerHealth = players.get<HealthComponent>(player).healthPoints;
        for (auto& bullet : bullets) {
            BulletTypeComponent& projectileType =
                bullets.get<BulletTypeComponent>(bullet);
            if (projectileType.type == EntityType::ENEMY) {
                TransformComponent& bulletTransform =
                    bullets.get<TransformComponent>(bullet);
                DamageComponent& bulletDamage = 
                    bullets.get<DamageComponent>(bullet);
                if (checkCollition(std::pair(playerTransform.width * playerTransform.scaleX, playerTransform.height * playerTransform.scaleY),
                std::pair(bulletTransform.height * bulletTransform.scaleY, bulletTransform.width * bulletTransform.scaleX), std::pair(playerTransform.x, playerTransform.y),
                std::pair(bulletTransform.x, bulletTransform.y))) {
                    playerHealth -= bulletDamage.damage;
                    registry.destroy(bullet);
                }
            }
        }
    }
}

