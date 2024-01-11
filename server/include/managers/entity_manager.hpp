#if !defined(ENTITY_MANAGER_HPP)
#    define ENTITY_MANAGER_HPP

#    include "../../../common/components/component_includes.hpp"
#    include "../../../libs/EnTT/entt.hpp"

#    include "../config.hpp"

/**
 * @file entity_manager.hpp
 * @brief Defines the EntityManager class.
 */

/**
 * @class EntityManager
 * @brief This class is responsible for managing entities in the game.
 *
 * It uses the EnTT library to create and manage entities.
 */
class EntityManager {
private:
    /**
     * @brief The registry from EnTT that the manager uses for entity operations.
     */
    entt::registry _registry;

public:
    /**
     * @brief Constructs a new EntityManager.
     */
    EntityManager() = default;

    /**
     * @brief Destroys the EntityManager, clearing the registry.
     */
    ~EntityManager() { _registry.clear(); }

    /**
     * @brief Returns the registry.
     *
     * @return The registry.
     */
    entt::registry& getRegistry() { return _registry; }

    /**
     * @brief Creates a new player entity.
     *
     * @param hint A hint for the entity creation.
     * @return The created player entity.
     */
    entt::entity createPlayer(entt::entity hint);

    /**
     * @brief Creates a new normal enemy entity.
     *
     * @param spawnHeight The height at which to spawn the enemy.
     * @param speed The speed of the enemy.
     * @return The created enemy entity.
     */
    entt::entity createNormalEnemy(std::pair<float, float> position, float speed);

    /**
     * @brief Creates a new projectile entity.
     *
     * @param dx The x direction of the projectile.
     * @param dy The y direction of the projectile.
     * @param x The x position of the projectile.
     * @param y The y position of the projectile.
     * @param velocity The velocity of the projectile.
     * @return The created projectile entity.
     */
    entt::entity createProjectile(
        entt::entity hint, std::pair<float, float> direction, std::pair<float, float> position,
        float velocity, EntityType type, std::uint32_t ownerId
    );
};

#endif  // ENTITY_MANAGER_HPP
