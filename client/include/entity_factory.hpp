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

    entt::entity createPlayer(entt::entity hint, std::pair<float, float> position);

    entt::entity createNormalEnemy(entt::entity hint, std::pair<float, float> position);

    entt::entity createFastEnemy(entt::entity hint, std::pair<float, float> position);

    entt::entity createProjectile(entt::entity hint, std::pair<float, float> position);

    entt::entity createEnemyProjectile(entt::entity hint, std::pair<float, float> position);

    entt::entity createExplosion(std::pair<float, float> position);

    entt::entity createBackground();

    entt::entity createMainMenu();

    entt::entity createWaveTransition(std::string title);

    entt::entity createPlanet(float x, float y, std::string randomFilepath);
};

#endif  // ENTITY_FACTORY_HPP
