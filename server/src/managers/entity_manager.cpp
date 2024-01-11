#include "../../include/managers/entity_manager.hpp"

entt::entity EntityManager::createPlayer(entt::entity hint)
{
    auto player = _registry.create(hint);

    TransformComponent transformComponent = {
        .x = 12.0f,
        .y = 0.0f,
        .rotation = 0.0f,
        .scaleX = 1.0f,
        .scaleY = 1.0f,
        .orientation = 0.0f,
    };

    _registry.emplace<TransformComponent>(player, transformComponent);

    _registry.emplace<VelocityComponent>(player, 0.0f, 0.0f, 10.0f);
    _registry.emplace<WeaponComponent>(
        player, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100, false
    );
    _registry.emplace<ScoreComponent>(player, 0, 1.0f, 0);
    _registry.emplace<HealthComponent>(player, 100.0f);
    _registry.emplace<PlayerComponent>(player);

    return player;
}

entt::entity EntityManager::createNormalEnemy(float spawnHeight, float speed)
{
    auto enemy = _registry.create();

    _registry.emplace<EnemyAIComponent>(enemy);
    _registry.emplace<TransformComponent>(
        enemy, WINDOW_WIDTH + 128.0f, spawnHeight, 0.0f, 1.0f, 1.0f, 0.0f
    );
    _registry.emplace<VelocityComponent>(enemy, -1.0f, 0.0f, speed);
    _registry.emplace<WeaponComponent>(
        enemy, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100, false
    );
    _registry.emplace<ScoreComponent>(enemy, 0, 1.0f, 0);
    _registry.emplace<HealthComponent>(enemy, 100.0f);

    return enemy;
}

entt::entity EntityManager::createProjectile(
    entt::entity hint, float dx, float dy, float x, float y, float velocity, EntityType type,
    std::uint32_t ownerId
)
{
    auto projectile = _registry.create(hint);
    _registry.emplace<OwnerComponent>(projectile, ownerId);
    _registry.emplace<BulletTypeComponent>(projectile, type);
    _registry.emplace<TransformComponent>(projectile, x, y, 0.0f, 1.0f, 1.0f, 0.0f);
    _registry.emplace<VelocityComponent>(projectile, dx, dy, velocity);
    _registry.emplace<DamageComponent>(projectile, 100.0f);

    return projectile;
}
