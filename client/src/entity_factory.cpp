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

entt::entity EntityFactory::createNormalEnemy(entt::entity hint, float spawnHeight, float speed)
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
    _registry.emplace<EnemyComponent>(enemy);
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

entt::entity EntityFactory::createFastEnemy(entt::entity hint, float spawnWidth, float speed)
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
    _registry.emplace<EnemyComponent>(enemy);
    _registry.emplace<RenderableComponent>(enemy, std::move(renderable));
    _registry.emplace<TransformComponent>(enemy, spawnWidth, -128.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    _registry.emplace<VelocityComponent>(enemy, 0.0f, 1.0f, speed);
    _registry.emplace<WeaponComponent>(
        enemy, WeaponType::NORMAL, std::vector<std::string>{}, 1.0f, 100, false
    );
    _registry.emplace<ScoreComponent>(enemy, 0, 1.0f, 0);
    _registry.emplace<HealthComponent>(enemy, 100.0f);
    _registry.emplace<SceneComponent>(enemy, GameScenes::InGame);
    return enemy;
}

entt::entity EntityFactory::createProjectile(
    entt::entity hint, float dx, float dy, float x, float y, float velocity
)
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

entt::entity EntityFactory::createEnemyProjectile(
    entt::entity hint, float dx, float dy, float x, float y, float velocity
)
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

entt::entity EntityFactory::createMainMenu()
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
    renderable.text.setPosition(
        _window.getSize().x + titleBounds.width / 2, _window.getSize().y / 2
    );
    _registry.emplace<TransformComponent>(
        transitionTitle, _window.getSize().x + titleBounds.width / 2.0f, _window.getSize().y / 2.0f,
        0.0f, 1.0f, 1.0f, 0.0f
    );
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
