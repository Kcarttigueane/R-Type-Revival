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
            _resourceManager.loadTexture(_assetsPath + "/bydos/bydos.png");
        sf::IntRect initialFrameRect(277, 44, 86, 40);
        RenderableComponent renderable;
        renderable.texture = texture;
        renderable.sprite.setTexture(*texture);
        renderable.sprite.setScale(sf::Vector2f(2.0, 2.0));
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
            _resourceManager.loadTexture(_assetsPath + "/bydos/bydos.png");
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
            enemy, WINDOW_WIDTH + 128.0f, spawnHeight, 0.0f, 1.0f, 1.0f, 0.0f
        );
        _registry.emplace<VelocityComponent>(enemy, -1.0f, 0.0f, speed);
        _registry.emplace<WeaponComponent>(
            enemy, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100,
            false
        );
        _registry.emplace<ScoreComponent>(enemy, 0, 1.0f, 0);
        _registry.emplace<HealthComponent>(enemy, 100.0f);
        _registry.emplace<SceneComponent>(enemy, GameScenes::InGame);

        auto soundBuffer = _resourceManager.loadSoundBuffer(
            _assetsPath + "/sound_fx/explosion.wav"
        );

        SoundComponent sound(*soundBuffer);
        sound.setVolumeLevel(10.0f);

        _registry.emplace<SoundComponent>(enemy, std::move(sound));

        return enemy;
    }

    entt::entity createProjectile(
        float dx, float dy, float x, float y, float velocity
    )
    {
        auto projectile = _registry.create();
        auto texture = _resourceManager.loadTexture(
            _assetsPath + "/player/player_shots_revamped.png"
        );
        sf::IntRect initialFrameRect(0, 0, 54, 12);
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
        _registry.emplace<HoldAnimationComponent>(projectile, 6, 0.5f, true);
        return projectile;
    }

    entt::entity createExplosion(float x, float y)
    {
        auto explosion = _registry.create();
        auto texture = _resourceManager.loadTexture(
            _assetsPath + "/explosions/ships_explosions.png"
        );
        sf::IntRect initialFrameRect(0, 0, 256, 256);
        RenderableComponent renderable;
        renderable.texture = texture;
        renderable.sprite.setPosition(sf::Vector2f(x, y));
        renderable.sprite.setTexture(*texture);
        renderable.sprite.setScale(sf::Vector2f(0.75f, 0.75f));
        renderable.frameRect = initialFrameRect;
        renderable.sprite.setTextureRect(initialFrameRect);
        _registry.emplace<RenderableComponent>(
            explosion, std::move(renderable)
        );
        _registry.emplace<TransformComponent>(
            explosion, x, y, 0.0f, 1.0f, 1.0f, 0.0f
        );
        _registry.emplace<SceneComponent>(explosion, GameScenes::InGame);
        _registry.emplace<SingleAnimationComponent>(explosion, 11, 0.75f);
        return explosion;
    }

    entt::entity createBackground()
    {
        auto texture = _resourceManager.loadTexture(
            _assetsPath + "/background/layer_3/space_background.png"
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

    entt::entity createMainMenuTitle()
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

    entt::entity createButton(
        const std::string& path, const std::string& label, int index, bool isSelected
    )
    {
        auto button = _registry.create();
        auto texture = _resourceManager.loadTexture(path);

        float buttonWidth = 310.0f * 0.4f;
        float buttonSpacing = 75.0f;
        int totalButtons = 5;
        float totalWidth =
            totalButtons * buttonWidth + (totalButtons - 1) * buttonSpacing;
        float firstButtonX =
            _window.getSize().x / 2.0f - totalWidth / 2.0f + buttonWidth / 2.0f;
        float buttonX = firstButtonX + index * (buttonWidth + buttonSpacing);
        float buttonY = _window.getSize().y * 0.6f;

        RenderableComponent renderable;
        renderable.texture = texture;
        renderable.sprite.setTexture(*texture);
        renderable.sprite.setScale(sf::Vector2f(0.4f, 0.4f));

        sf::FloatRect bounds = renderable.sprite.getLocalBounds();
        renderable.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        renderable.sprite.setPosition(buttonX, buttonY);

        _registry.emplace<RenderableComponent>(button, std::move(renderable));
        _registry.emplace<SceneComponent>(button, GameScenes::MainMenu);
        _registry.emplace<MenuItemComponent>(button, label, index, isSelected);
        _registry.emplace<TransformComponent>(
            button, buttonX, buttonY, 0.0f, 1.0f, 1.0f, 0.0f
        );

        return button;
    };

    entt::entity createSelectedLabel()
    {
        auto font =
            _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
        auto labelEntity = _registry.create();
        RenderableComponent renderable;
        renderable.text.setFont(*font);
        renderable.text.setString("");
        renderable.text.setCharacterSize(48);
        renderable.text.setFillColor(sf::Color::White
        );

        renderable.text.setPosition(
            _window.getSize().x / 2, _window.getSize().y * 0.7
        );

        _registry.emplace<RenderableComponent>(
            labelEntity, std::move(renderable)
        );
        _registry.emplace<SceneComponent>(labelEntity, GameScenes::MainMenu);

        return labelEntity;
    };

    entt::entity createSettingsItem(
        const std::string& settingName,
        const std::vector<std::string>& settingValues, int currentValueIndex,
        int index
    )
    {
        auto font =
            _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
        auto settingsItem = _registry.create();

        float startingY = _window.getSize().y * 0.3f;
        float spacing = 50.0f;
        float menuItemY = startingY + index * spacing;

        RenderableComponent renderable;

        renderable.text.setFont(*font);
        renderable.text.setString(
            settingName + ": " + settingValues[currentValueIndex]
        );
        renderable.text.setCharacterSize(48);
        renderable.text.setFillColor(sf::Color::White);
        renderable.text.setPosition(
            _window.getSize().x / 4, menuItemY
        );
        _registry.emplace<RenderableComponent>(settingsItem, renderable);

        _registry.emplace<SceneComponent>(settingsItem, GameScenes::Settings);
        _registry.emplace<SettingItemComponent>(
            settingsItem, settingName, settingValues, currentValueIndex,
            index == 0
        );

        return settingsItem;
    };
};

#endif  // ENTITY_FACTORY_HPP
