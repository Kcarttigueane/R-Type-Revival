#if !defined(ENTITY_FACTORY_HPP)
#    define ENTITY_FACTORY_HPP

#    include "../../libs/EnTT/entt.hpp"
#    include "./config.hpp"

#    include "../../common/components/component_includes.hpp"

#    include "../../build/common/proto/r_type.pb.h"
#    include "./managers/resource_manager.hpp"

using std::string;

/**
 * @file entity_factory.hpp
 * @brief File containing the EntityFactory class.
 */

/**
 * @class EntityFactory
 * @brief Class responsible for creating different types of entities.
 *
 * This class uses the EnTT library to create entities and assign them components.
 * It interacts with the ResourceManager to load resources and the SFML RenderWindow to display entities.
 */
class EntityFactory {
private:
    string _assetsPath = ASSETS_DIR;    ///< Path to the assets directory.
    entt::registry& _registry;          ///< Reference to the EnTT registry.
    ResourceManager& _resourceManager;  ///< Reference to the ResourceManager.
    sf::RenderWindow& _window;          ///< Reference to the SFML RenderWindow.

public:
    /**
     * @brief Constructs a new EntityFactory object.
     * @param registry Reference to the EnTT registry.
     * @param resourceManager Reference to the ResourceManager.
     * @param window Reference to the SFML RenderWindow.
     */
    EntityFactory(
        entt::registry& registry, ResourceManager& resourceManager, sf::RenderWindow& window
    );

    /**
     * @brief Default destructor.
     */
    ~EntityFactory() = default;

    /**
     * @brief Creates a new player entity.
     * @param hint A hint for the entity identifier.
     * @param position The initial position of the player.
     * @return The created player entity.
     */
    entt::entity createPlayer(entt::entity hint, std::pair<float, float> position);

    /**
     * @brief Creates a new enemy entity.
     * @param type The type of the enemy.
     * @param hint A hint for the entity identifier.
     * @param position The initial position of the enemy.
     * @return The created enemy entity.
     */
    entt::entity createEnemy(
        rtype::EnemyType type, entt::entity hint, std::pair<float, float> position
    );

    /**
     * @brief Creates a new normal enemy entity.
     * @param hint A hint for the entity identifier.
     * @param position The initial position of the enemy.
     * @return The created enemy entity.
     */
    entt::entity createNormalEnemy(entt::entity hint, std::pair<float, float> position);

    /**
     * @brief Creates a new fast enemy entity.
     * @param hint A hint for the entity identifier.
     * @param position The initial position of the enemy.
     * @return The created enemy entity.
     */
    entt::entity createFastEnemy(entt::entity hint, std::pair<float, float> position);

    /**
     * @brief Creates a new projectile entity.
     * @param hint A hint for the entity identifier.
     * @param position The initial position of the projectile.
     * @return The created projectile entity.
     */
    entt::entity createProjectile(entt::entity hint, std::pair<float, float> position);

    /**
     * @brief Creates a new enemy projectile entity.
     * @param hint A hint for the entity identifier.
     * @param position The initial position of the projectile.
     * @return The created projectile entity.
     */
    entt::entity createEnemyProjectile(entt::entity hint, std::pair<float, float> position);

    /**
     * @brief Creates a new explosion entity.
     * @param position The initial position of the explosion.
     * @return The created explosion entity.
     */
    entt::entity createExplosion(std::pair<float, float> position);

    /**
     * @brief Creates a new background entity.
     * @param hint A hint for the entity identifier.
     * @return The created background entity.
     */
    entt::entity createBackground(entt::entity hint);

    /**
     * @brief Creates a new main menu entity.
     * @param hint A hint for the entity identifier.
     * @return The created main menu entity.
     */
    entt::entity createMainMenu(entt::entity hint);

    /**
     * @brief Creates a new wave transition entity.
     * @param hint A hint for the entity identifier.
     * @param title The title of the wave transition.
     * @return The created wave transition entity.
     */
    entt::entity createWaveTransition(entt::entity hint, std::string title);

    /**
     * @brief Creates a new planet entity.
     * @param hint A hint for the entity identifier.
     * @param position The initial position of the planet.
     * @param randomFilepath The file path to the planet image.
     * @return The created planet entity.
     */
    entt::entity createPlanet(
        entt::entity hint, std::pair<float, float> position, std::string randomFilepath
    );

    /**
     * @brief Creates a new health entity.
     * @param hint A hint for the entity identifier.
     * @return The created health entity.
     */
    entt::entity createHealth(entt::entity hint);
};

#endif  // ENTITY_FACTORY_HPP
