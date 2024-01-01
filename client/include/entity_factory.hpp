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
        entt::registry& registry, ResourceManager& resourceManager,
        sf::RenderWindow& window
    )
        : _registry(registry),
          _resourceManager(resourceManager),
          _window(window){};

    ~EntityFactory() = default;

    entt::entity createPlayer()
    {
        auto player = _registry.create();
        auto texture =
            _resourceManager.loadTexture(_assetsPath + "/Player/spaceship.gif");
        sf::IntRect initialFrameRect(66, 0, 33, 17);

        RenderableComponent renderable;
        renderable.texture = texture;
        renderable.sprite.setTexture(*texture);
        renderable.sprite.setScale(sf::Vector2f(5.0, 5.0));
        renderable.frameRect = initialFrameRect;
        renderable.sprite.setTextureRect(initialFrameRect);

        _registry.emplace<RenderableComponent>(player, std::move(renderable));

        _registry.emplace<TransformComponent>(
            player, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f
        );

        _registry.emplace<VelocityComponent>(player, 0.0f, 0.0f, 10.0f);

        _registry.emplace<WeaponComponent>(
            player, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100,
            false
        );

        _registry.emplace<ScoreComponent>(player, 0, 1.0f, 0);

        _registry.emplace<HealthComponent>(player, 100.0f);

        _registry.emplace<SceneComponent>(player, GameScenes::InGame);

        _registry.emplace<PlayerComponent>(player);
        return player;
    }

    entt::entity createNormalEnemy(float spawnHeight, float speed)
    {
        auto enemy = _registry.create();
        auto texture =
            _resourceManager.loadTexture(_assetsPath + "/Bydos/Bydos.png");
        sf::IntRect initialFrameRect(32, 48, 64, 32);

        RenderableComponent renderable;
        renderable.texture = texture;
        renderable.sprite.setPosition(sf::Vector2f(2100.0f, spawnHeight));
        renderable.sprite.setTexture(*texture);
        renderable.sprite.setScale(sf::Vector2f(-2.0, 2.0));
        renderable.frameRect = initialFrameRect;
        renderable.sprite.setTextureRect(initialFrameRect);

        _registry.emplace<EnemyAIComponent>(enemy);

        _registry.emplace<RenderableComponent>(enemy, std::move(renderable));

        _registry.emplace<TransformComponent>(
            enemy, 2100.0f, spawnHeight, 0.0f, 1.0f, 1.0f, 0.0f
        );

        _registry.emplace<VelocityComponent>(enemy, -1.0f, 0.0f, speed);

        _registry.emplace<WeaponComponent>(
            enemy, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100,
            false
        );

        _registry.emplace<ScoreComponent>(enemy, 0, 1.0f, 0);

        _registry.emplace<HealthComponent>(enemy, 100.0f);

        _registry.emplace<SceneComponent>(enemy, GameScenes::InGame);
        return enemy;
    }

    entt::entity createProjectile(
        float dx, float dy, float x, float y, float velocity
    )
    {
        auto projectile = _registry.create();
        auto texture = _resourceManager.loadTexture(
            _assetsPath + "/Player/Player_shots.png"
        );
        sf::IntRect initialFrameRect(45, 62, 32, 8);

        RenderableComponent renderable;
        renderable.texture = texture;
        renderable.sprite.setPosition(sf::Vector2f(x, y));
        renderable.sprite.setTexture(*texture);
        renderable.sprite.setScale(sf::Vector2f(1.0f, 1.0f));
        renderable.frameRect = initialFrameRect;
        renderable.sprite.setTextureRect(initialFrameRect);

        _registry.emplace<RenderableComponent>(
            projectile, std::move(renderable)
        );

        _registry.emplace<TransformComponent>(
            projectile, x, y, 0.0f, 1.0f, 1.0f, 0.0f
        );

        _registry.emplace<VelocityComponent>(projectile, dx, dy, velocity);

        _registry.emplace<DamageComponent>(projectile, 100.0f);

        _registry.emplace<SceneComponent>(projectile, GameScenes::InGame);

        return projectile;
    }

    entt::entity createBackground()
    {
        auto texture = _resourceManager.loadTexture(
            _assetsPath + "/Background/Layer 3/Space_background.png"
        );

        auto background = _registry.create();
        RenderableComponent renderable;
        renderable.texture = texture;
        renderable.sprite.setTexture(*texture);
        renderable.sprite.setPosition(sf::Vector2f(0.0f, 0.0f));

        _registry.emplace<RenderableComponent>(
            background, std::move(renderable)
        );

        _registry.emplace<TransformComponent>(
            background, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f
        );
        _registry.emplace<ParallaxComponent>(background, 100.0f);
        _registry.emplace<SceneComponent>(background);

        return background;
    };

    entt::entity createMainMenu()
    {
        auto font =
            _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");

        auto mainMenuTitle = _registry.create();
        RenderableComponent renderable;

        renderable.text.setFont(*font);

        renderable.text.setString("R-Type");
        renderable.text.setCharacterSize(96);
        sf::FloatRect titleBounds = renderable.text.getLocalBounds();
        renderable.text.setOrigin(
            titleBounds.width / 2, titleBounds.height / 2
        );
        renderable.text.setPosition(
            _window.getSize().x / 2, _window.getSize().y * 0.20
        );

        _registry.emplace<RenderableComponent>(
            mainMenuTitle, std::move(renderable)
        );
        _registry.emplace<SceneComponent>(mainMenuTitle, GameScenes::MainMenu);

        return mainMenuTitle;
    };
};

#endif  // ENTITY_FACTORY_HPP
