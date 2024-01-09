#if !defined(ENTITY_MANAGER_HPP)
#    define ENTITY_MANAGER_HPP

#    include "../../../common/components/component_includes.hpp"
#    include "../../../libs/EnTT/entt.hpp"

#    include "../config.hpp"

class EntityManager {
private:
    entt::registry _registry;

public:
    EntityManager() = default;

    ~EntityManager() { _registry.clear(); }

    entt::registry& getRegistry() { return _registry; }

    // ! Factory methods

    entt::entity createPlayer(entt::entity hint);

    entt::entity createNormalEnemy(float spawnHeight, float speed);

    entt::entity createProjectile(float dx, float dy, float x, float y, float velocity);
};

#endif  // ENTITY_MANAGER_HPP
