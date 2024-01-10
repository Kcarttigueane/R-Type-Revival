#include "../include/entity_factory.hpp"

entt::entity EntityFactory::createPlayer(entt::entity hint)
{
    auto player = _registry.create(hint);
    auto texture = _resourceManager.loadTexture(_assetsPath + "/bydos/bydos.png");
    sf::IntRect initialFrameRect(277, 44, 86, 40);
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(2.0, 2.0));
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);

    _registry.emplace<RenderableComponent>(player, std::move(renderable));
    _registry.emplace<TransformComponent>(player, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    _registry.emplace<VelocityComponent>(player, 0.0f, 0.0f, 10.0f);
    _registry.emplace<WeaponComponent>(
        player, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100, false
    );
    _registry.emplace<ScoreComponent>(player, 0, 1.0f, 0);
    _registry.emplace<HealthComponent>(player, 100.0f);
    _registry.emplace<SceneComponent>(player, GameScenes::InGame);
    _registry.emplace<PlayerComponent>(player);
    return player;
}

entt::entity EntityFactory::createNormalEnemy(float spawnHeight, float speed)
{
    auto enemy = _registry.create();
    auto texture = _resourceManager.loadTexture(_assetsPath + "/bydos/bydos.png");
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
        enemy, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100, false
    );
    _registry.emplace<ScoreComponent>(enemy, 0, 1.0f, 0);
    _registry.emplace<HealthComponent>(enemy, 100.0f);
    _registry.emplace<SceneComponent>(enemy, GameScenes::InGame);

    return enemy;
}

entt::entity EntityFactory::createFastEnemy(float spawnWidth, float speed)
{
    auto enemy = _registry.create();
    auto texture = _resourceManager.loadTexture(_assetsPath + "/bydos/bydos.png");
    sf::IntRect initialFrameRect(150, 48, 82, 32);
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(spawnWidth, -128.0f));
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(2.0, 2.0));
    renderable.sprite.setRotation(90.0f);
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    _registry.emplace<EnemyAIComponent>(enemy);
    _registry.emplace<RenderableComponent>(enemy, std::move(renderable));
    _registry.emplace<TransformComponent>(
        enemy, spawnWidth, -128.0f, 0.0f, 1.0f, 1.0f, 0.0f
    );
    _registry.emplace<VelocityComponent>(enemy, 0.0f, 1.0f, speed);
    _registry.emplace<WeaponComponent>(
        enemy, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100, false
    );
    _registry.emplace<ScoreComponent>(enemy, 0, 1.0f, 0);
    _registry.emplace<HealthComponent>(enemy, 100.0f);
    _registry.emplace<SceneComponent>(enemy, GameScenes::InGame);
    return enemy;
}

entt::entity EntityFactory::createProjectile(float dx, float dy, float x, float y, float velocity)
{
    auto projectile = _registry.create();
    auto texture = _resourceManager.loadTexture(_assetsPath + "/player/player_shots_revamped.png");
    sf::IntRect initialFrameRect(0, 0, 54, 12);
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(x, y));
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(1.0f, 1.0f));
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    _registry.emplace<RenderableComponent>(projectile, std::move(renderable));
    _registry.emplace<TransformComponent>(projectile, x, y, 0.0f, 1.0f, 1.0f, 0.0f);
    _registry.emplace<VelocityComponent>(projectile, dx, dy, velocity);
    _registry.emplace<DamageComponent>(projectile, 100.0f);
    _registry.emplace<SceneComponent>(projectile, GameScenes::InGame);
    _registry.emplace<HoldAnimationComponent>(projectile, 6, 0.2f, true);
    _registry.emplace<PlayerProjectileComponent>(projectile);
    return projectile;
}

entt::entity EntityFactory::createEnemyProjectile(float dx, float dy, float x, float y, float velocity)
{
    auto projectile = _registry.create();
    auto texture = _resourceManager.loadTexture(_assetsPath + "/bydos/enemy_shot.png");
    sf::IntRect initialFrameRect(0, 0, 7, 6);
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(x, y));
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(5.0f, 5.0f));
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    _registry.emplace<RenderableComponent>(projectile, std::move(renderable));
    _registry.emplace<TransformComponent>(projectile, x, y, 0.0f, 1.0f, 1.0f, 0.0f);
    _registry.emplace<VelocityComponent>(projectile, dx, dy, velocity);
    _registry.emplace<DamageComponent>(projectile, 100.0f);
    _registry.emplace<SceneComponent>(projectile, GameScenes::InGame);
    _registry.emplace<InfiniteAnimationComponent>(projectile, 4, 0.25f);
    _registry.emplace<EnemyProjectileComponent>(projectile);
    return projectile;
}

entt::entity EntityFactory::createExplosion(float x, float y)
{
    auto explosion = _registry.create();
    auto texture = _resourceManager.loadTexture(_assetsPath + "/explosions/ships_explosions.png");
    sf::IntRect initialFrameRect(0, 0, 256, 256);
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(x, y));
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(0.75f, 0.75f));
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    _registry.emplace<RenderableComponent>(explosion, std::move(renderable));
    _registry.emplace<TransformComponent>(explosion, x, y, 0.0f, 1.0f, 1.0f, 0.0f);
    _registry.emplace<SceneComponent>(explosion, GameScenes::InGame);
    _registry.emplace<SingleAnimationComponent>(explosion, 11, 0.75f);
    return explosion;
}

entt::entity EntityFactory::createBackground()
{
    auto texture =
        _resourceManager.loadTexture(_assetsPath + "/background/layer_3/space_background.png");
    auto background = _registry.create();
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setPosition(sf::Vector2f(0.0f, 0.0f));
    _registry.emplace<RenderableComponent>(background, std::move(renderable));
    _registry.emplace<TransformComponent>(background, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    _registry.emplace<ParallaxComponent>(background, 100.0f);
    _registry.emplace<SceneComponent>(background);
    return background;
};

entt::entity EntityFactory::createWaveTransition(std::string title)
{
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    auto transitionTitle = _registry.create();
    RenderableComponent renderable;
    renderable.text.setFont(*font);
    renderable.text.setString(title);
    renderable.text.setCharacterSize(96);
    sf::FloatRect titleBounds = renderable.text.getLocalBounds();
    renderable.text.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    renderable.text.setPosition(_window.getSize().x + titleBounds.width / 2, _window.getSize().y / 2);
    _registry.emplace<TransformComponent>(transitionTitle, _window.getSize().x + titleBounds.width / 2.0f, _window.getSize().y / 2.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    _registry.emplace<VelocityComponent>(transitionTitle, -1.0f, 0.0f, 5.0f);
    _registry.emplace<RenderableComponent>(transitionTitle, std::move(renderable));
    _registry.emplace<SceneComponent>(transitionTitle, GameScenes::InGame);
    return transitionTitle;
}


entt::entity EntityFactory::createPlanet(float x, float y, std::string randomFilepath)
{
    auto planet = _registry.create();
    auto texture = _resourceManager.loadTexture(_assetsPath + randomFilepath);

    sf::IntRect initialFrameRect(0, 0, 64, 64);
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(x, y));
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(2.0f, 2.0f));
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    _registry.emplace<RenderableComponent>(planet, std::move(renderable));
    _registry.emplace<TransformComponent>(planet, x, y, 0.0f, 1.0f, 1.0f, 0.0f);
    _registry.emplace<PlanetComponent>(planet);
    _registry.emplace<SceneComponent>(planet);
    _registry.emplace<InfiniteAnimationComponent>(planet, 256, 8.6f);
    return planet;
}

entt::entity EntityFactory::createMainMenuTitle()
{
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    auto mainMenuTitle = _registry.create();
    RenderableComponent renderable;
    renderable.text.setFont(*font);
    renderable.text.setString("R-Type");
    renderable.text.setCharacterSize(96);
    sf::FloatRect titleBounds = renderable.text.getLocalBounds();
    renderable.text.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    renderable.text.setPosition(_window.getSize().x / 2, _window.getSize().y * 0.20);
    _registry.emplace<RenderableComponent>(mainMenuTitle, std::move(renderable));
    _registry.emplace<SceneComponent>(mainMenuTitle, GameScenes::MainMenu);
    return mainMenuTitle;
}

entt::entity EntityFactory::createButton(
    const std::string& path, const std::string& label, int index, bool isSelected
)
{
    auto button = _registry.create();
    auto texture = _resourceManager.loadTexture(path);

    float buttonWidth = 310.0f * 0.4f;
    float buttonSpacing = 75.0f;
    int totalButtons = 5;
    float totalWidth = totalButtons * buttonWidth + (totalButtons - 1) * buttonSpacing;
    float firstButtonX = _window.getSize().x / 2.0f - totalWidth / 2.0f + buttonWidth / 2.0f;
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
    _registry.emplace<TransformComponent>(button, buttonX, buttonY, 0.0f, 1.0f, 1.0f, 0.0f);

    return button;
}

entt::entity EntityFactory::createSelectedLabel()
{
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    auto labelEntity = _registry.create();
    RenderableComponent renderable;
    renderable.text.setFont(*font);
    renderable.text.setString("");
    renderable.text.setCharacterSize(48);
    renderable.text.setFillColor(sf::Color::White);

    renderable.text.setPosition(_window.getSize().x / 2, _window.getSize().y * 0.7);

    _registry.emplace<RenderableComponent>(labelEntity, std::move(renderable));
    _registry.emplace<SceneComponent>(labelEntity, GameScenes::MainMenu);

    return labelEntity;
}

entt::entity EntityFactory::createSettingsItem(
    const std::string& settingName, const std::vector<std::string>& settingValues,
    int currentValueIndex, int index
)
{
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    auto settingsItem = _registry.create();

    float startingY = _window.getSize().y * 0.3f;
    float spacing = 50.0f;
    float menuItemY = startingY + index * spacing;

    RenderableComponent renderable;

    renderable.text.setFont(*font);
    renderable.text.setString(settingName + ": " + settingValues[currentValueIndex]);
    renderable.text.setCharacterSize(48);
    renderable.text.setFillColor(sf::Color::White);
    renderable.text.setPosition(_window.getSize().x / 4, menuItemY);
    _registry.emplace<RenderableComponent>(settingsItem, renderable);

    _registry.emplace<SceneComponent>(settingsItem, GameScenes::Settings);
    _registry.emplace<SettingItemComponent>(
        settingsItem, settingName, settingValues, currentValueIndex, index == 0
    );

    return settingsItem;
}

entt::entity EntityFactory::createAboutMenu()
{
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    auto aboutMenuEntity = _registry.create();
    RenderableComponent renderable;

    std::string aboutText =
        "About R-Type 2\n\n"
        "Developed by a team of passionate game enthusiasts, R-Type 2 \n"
        "brings together a blend of engaging gameplay and creative \n"
        "design. Our team is committed to delivering an immersive and \n"
        "enjoyable experience for all players.\n\n"

        "Development Team\n"
        "Kevin\n"
        "Jules\n"
        "Lucas\n"
        "Tom\n"
        "Dylan\n\n"

        "Copyright © 2024 Leaving tek after this. All rights "
        "reserved.\n\n"

        "Special Thanks\n"
        "We would like to extend our heartfelt thanks to our families, \n"
        "friends, and the gaming community for their unwavering support \n"
        "and valuable feedback throughout the development process. Your \n"
        "encouragement has been instrumental in bringing this project to \n"
        "life.\n\n"

        "Stay Connected";

    renderable.text.setFont(*font);
    renderable.text.setString(aboutText);
    renderable.text.setCharacterSize(32);
    renderable.text.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = renderable.text.getLocalBounds();
    renderable.text.setOrigin(textBounds.width / 2, textBounds.height / 2);
    renderable.text.setPosition(_window.getSize().x / 2, _window.getSize().y * 0.50);

    _registry.emplace<RenderableComponent>(aboutMenuEntity, std::move(renderable));
    _registry.emplace<SceneComponent>(aboutMenuEntity, GameScenes::About);

    return aboutMenuEntity;
}