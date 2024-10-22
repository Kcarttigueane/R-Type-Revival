#include "../../include/managers/entity_manager.hpp"

entt::entity EntityManager::createPlayer(entt::entity hint)
{
    auto player = _registry.create(hint);

    TransformComponent transformComponent = {
        .x = WINDOW_HEIGHT / 2.0f,
        .y = WINDOW_WIDTH / 6.0f,
        .scaleX = 2.0f,
        .scaleY = 2.0f,
        .width = 86,
        .height = 40,
    };
    _registry.emplace<TransformComponent>(player, transformComponent);

    _registry.emplace<VelocityComponent>(player, 0.0f, 0.0f, 10.0f);
    _registry.emplace<WeaponComponent>(
        player, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100, false
    );
    _registry.emplace<ScoreComponent>(player, 0, 1.0f, 0);
    _registry.emplace<HealthComponent>(player, 3.0f);
    _registry.emplace<PlayerComponent>(player);

    return player;
}

entt::entity EntityManager::createNormalEnemy(
    entt::entity hint, std::pair<float, float> position, float speed
)
{
    auto enemy = _registry.create(hint);
    _registry.emplace<EnemyComponent>(enemy);

    TransformComponent transformComponent = {
        .x = position.first,
        .y = position.second,
        .scaleX = 2.0f,
        .scaleY = 2.0f,
        .width = 64,
        .height = 32,
    };
    _registry.emplace<TransformComponent>(enemy, transformComponent);

    _registry.emplace<VelocityComponent>(enemy, -1.0f, 0.0f, speed);
    _registry.emplace<WeaponComponent>(
        enemy, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100, false
    );
    _registry.emplace<HealthComponent>(enemy, 1.0f);
    _registry.emplace<DamageComponent>(enemy, 3.0f);
    _registry.emplace<ClockComponent>(
        enemy, getRandomFloat(1.0f, 10.0f), std::chrono::_V2::steady_clock::now()
    );

    return enemy;
}

entt::entity EntityManager::createProjectile(
    entt::entity hint, std::pair<float, float> direction, std::pair<float, float> position,
    float velocity, EntityType type, std::uint32_t ownerId
)
{
    auto projectile = _registry.create(hint);
    _registry.emplace<OwnerComponent>(projectile, ownerId);
    _registry.emplace<BulletTypeComponent>(projectile, type);
    TransformComponent transformComponent = {
        .x = position.first,
        .y = position.second,
        .scaleX = 1.0f,
        .scaleY = 1.0f,
        .width = 12,
        .height = 12,
    };
    _registry.emplace<TransformComponent>(projectile, transformComponent);

    _registry.emplace<VelocityComponent>(projectile, direction.first, direction.second, velocity);
    _registry.emplace<DamageComponent>(projectile, 1.0f);

    return projectile;
}

entt::entity EntityManager::createFastEnemy(
    entt::entity hint, std::pair<float, float> position, float velocity
)
{
    auto enemy = _registry.create(hint);

    _registry.emplace<EnemyComponent>(enemy, EnemyType::FAST);

    TransformComponent transformComponent = {
        .x = position.first,
        .y = position.second,
        .scaleX = 2.0f,
        .scaleY = 2.0f,
        .width = 82,
        .height = 32,
    };

    _registry.emplace<TransformComponent>(enemy, transformComponent);
    _registry.emplace<VelocityComponent>(enemy, 0.0f, 1.0f, velocity);
    _registry.emplace<WeaponComponent>(
        enemy, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100, false
    );
    _registry.emplace<ScoreComponent>(enemy, 0, 1.0f, 0);
    _registry.emplace<HealthComponent>(enemy, 1.0f);
    _registry.emplace<DamageComponent>(enemy, 3.0f);

    return enemy;
}
