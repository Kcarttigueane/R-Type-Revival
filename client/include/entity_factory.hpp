#if !defined(ENTITY_FACTORY_HPP)
#    define ENTITY_FACTORY_HPP

#    include "../../libs/EnTT/entt.hpp"
#    include "./config.hpp"

#    include "../../common/components/component_includes.hpp"

#    include "./managers/resource_manager.hpp"

using std::string;

class EntityFactory {
private:
    string _assetsPath = ASSETS_DIR;
    entt::registry& _registry;
    ResourceManager& _resourceManager;
    sf::RenderWindow& _window;

public:
    EntityFactory(
        entt::registry& registry, ResourceManager& resourceManager, sf::RenderWindow& window
    )
        : _registry(registry), _resourceManager(resourceManager), _window(window){};

    ~EntityFactory() = default;

    entt::entity createPlayer(entt::entity hint);

    entt::entity createNormalEnemy(float spawnHeight, float speed);

    entt::entity createProjectile(float dx, float dy, float x, float y, float velocity);

    entt::entity createExplosion(float x, float y);

    entt::entity createBackground();

    entt::entity createMainMenu();

    entt::entity createLoseScene();

    entt::entity createWinScene();
};

#endif  // ENTITY_FACTORY_HPP

