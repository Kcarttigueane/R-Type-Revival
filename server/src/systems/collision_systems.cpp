#include "../../include/managers/game_manager.hpp"

// void collisionProjectileAndEnemy()
// {
//     auto enemies = _registry.view<EnemyAIComponent, RenderableComponent, HealthComponent>();
//     auto projectiles = _registry.view<RenderableComponent, DamageComponent>();

//     for (auto& enemy : enemies) {
//         sf::Sprite& enemySprite = enemies.get<RenderableComponent>(enemy).sprite;
//         float& enemyHealth = enemies.get<HealthComponent>(enemy).healthPoints;

//         for (auto& projectile : projectiles) {
//             sf::Sprite& projectileSprite =
//                 projectiles.get<RenderableComponent>(projectile).sprite;
//             float projectileDamage = projectiles.get<DamageComponent>(projectile).damage;

//             if (enemySprite.getGlobalBounds().intersects(projectileSprite.getGlobalBounds())) {
//                 enemyHealth -= projectileDamage;
//                 _registry.destroy(projectile);
//             }
//         }
//     }
// }

// void collisionEnemyAndPlayer()
// {
//     auto enemies = _registry.view<EnemyAIComponent, RenderableComponent>();
//     auto player = _playerProfileManager.getPlayerEntity();

//     for (auto& enemy : enemies) {
//         sf::Sprite& enemySprite = enemies.get<RenderableComponent>(enemy).sprite;
//         sf::Sprite& playerSprite = enemies.get<RenderableComponent>(player).sprite;
//         if (enemySprite.getGlobalBounds().intersects(playerSprite.getGlobalBounds())) {
//             deleteAIEnemies();
//         }
//     }
// };
