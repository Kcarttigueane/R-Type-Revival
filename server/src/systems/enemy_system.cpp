#include "../../include/managers/game_manager.hpp"

void GameManager::deleteDeadEnemies()
{
    entt::registry& registry = _entity_manager.getRegistry();
    auto enemies = registry.view<EnemyComponent, HealthComponent>();
    for (auto& enemy : enemies) {
        float& health = enemies.get<HealthComponent>(enemy).healthPoints;
        if (health <= 0.0f) {
            registry.destroy(enemy);
        }
    }
}

void GameManager::makeEnemyShoot()
{
    entt::registry& registry = _entity_manager.getRegistry();
    auto enemies = registry.view<EnemyComponent, ClockComponent, TransformComponent>();
    for (auto& enemy : enemies) {
        ClockComponent& timer = enemies.get<ClockComponent>(enemy);
        TransformComponent& transformable = enemies.get<TransformComponent>(enemy);
        auto now = std::chrono::_V2::steady_clock ::now();
        float deltaTime =
            std::chrono::duration<float, std::chrono::seconds::period>(now - timer.lastUpdate).count();
        if (deltaTime >= timer.timeout) {
            timer.lastUpdate = now;
            std::uint32_t bulletId = _idGenerator.generateId();
            entt::entity bulletEntityId = static_cast<entt::entity>(bulletId);
            entt::entity player = _entity_manager.selectRandomPlayer(registry);
            if (player != entt::null) {
                TransformComponent playerTransform = registry.get<TransformComponent>(player);
                std::pair<float, float> direction = getDirection(transformable.x, transformable.y, playerTransform.x, playerTransform.y);
                _entity_manager.createProjectile(bulletEntityId, direction,
                std::pair(transformable.x, transformable.y), 10.0f, EntityType::ENEMY, static_cast<uint32_t>(enemy));
            }
        }
    }
}