#include "../include/entity_factory.hpp"

entt::entity EntityFactory::createPlayer(entt::entity hint, std::pair<float, float> position)
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
    sf::Vector2f scaledSize = sf::Vector2f(86.0f, 40.0f);
    renderable.sprite.setOrigin(scaledSize.x / 2.0f, scaledSize.y / 2.0f);
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    renderable.text.setFont(*font);
    renderable.text.setString("100");
    renderable.text.setCharacterSize(50);
    renderable.text.setPosition(WINDOW_WIDTH - 200, 50);

    _registry.emplace<RenderableComponent>(player, std::move(renderable));

    ScoreComponent scoreComponent;
    scoreComponent.score = 100;
    scoreComponent.multiplier = 1.0f;
    scoreComponent.bonusPoints = 0;

    _registry.emplace<ScoreComponent>(player, scoreComponent);

    TransformComponent transformComponent = {
        .x = position.first,
        .y = position.second,
        .scaleX = 2.0f,
        .scaleY = 2.0f,
        .width = 86,
        .height = 40,
    };
    _registry.emplace<TransformComponent>(player, transformComponent);

    _registry.emplace<SceneComponent>(player, GameScenes::InGame);
    return player;
}

entt::entity EntityFactory::createProjectile(
    entt::entity hint, std::pair<float, float> position
)
{
    auto projectile = _registry.create(hint);
    auto texture = _resourceManager.loadTexture(_assetsPath + "/player/player_shots.png");
    sf::IntRect initialFrameRect(0, 0, 54, 12);

    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(position.first, position.second));
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(1.0f, 1.0f));
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    renderable.sprite.setOrigin(48 , 12 / 2.0f);
    _registry.emplace<RenderableComponent>(projectile, std::move(renderable));

    TransformComponent transformComponent = {
        .x = position.first,
        .y = position.second,
        .scaleX = 1.0f,
        .scaleY = 1.0f,
        .width = 54,
        .height = 12,
    };
    _registry.emplace<TransformComponent>(projectile, transformComponent);

    _registry.emplace<SceneComponent>(projectile, GameScenes::InGame);
    _registry.emplace<HoldAnimationComponent>(projectile, 6, 0.2f, true);
    return projectile;
}

entt::entity EntityFactory::createNormalEnemy(std::pair<float, float> position)
{
    auto enemy = _registry.create();
    auto texture = _resourceManager.loadTexture(_assetsPath + "/bydos/bydos.png");
    sf::IntRect initialFrameRect(32, 48, 64, 32);

    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(position.first, position.second));
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(-2.0, 2.0));
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    sf::Vector2f scaledSize = sf::Vector2f(64.0f, 32.0f) * 2.0f;
    renderable.sprite.setOrigin(scaledSize.x / 2.0f, scaledSize.y / 2.0f);
    _registry.emplace<RenderableComponent>(enemy, std::move(renderable));

    TransformComponent transformComponent = {
        .x = position.first,
        .y = position.second,
        .scaleX = 2.0f,
        .scaleY = 2.0f,
        .width = 64,
        .height = 32,
    };
    _registry.emplace<TransformComponent>(enemy, transformComponent);

    _registry.emplace<SceneComponent>(enemy, GameScenes::InGame);

    return enemy;
}

entt::entity EntityFactory::createFastEnemy(std::pair<float, float> position)
{
    auto enemy = _registry.create();
    auto texture = _resourceManager.loadTexture(_assetsPath + "/bydos/bydos.png");
    sf::IntRect initialFrameRect(150, 48, 82, 32);

    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(position.first, position.second));
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(2.0, 2.0));
    renderable.sprite.setRotation(90.0f);
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    sf::Vector2f scaledSize = sf::Vector2f(82.0f, 32.0f) * 2.0f;
    renderable.sprite.setOrigin(scaledSize.x / 2.0f, scaledSize.y / 2.0f);
    _registry.emplace<RenderableComponent>(enemy, std::move(renderable));

    TransformComponent transformComponent = {
        .x = position.first,
        .y = position.second,
        .scaleX = 2.0f,
        .scaleY = 2.0f,
        .width = 82,
        .height = 32,
    };
    _registry.emplace<TransformComponent>(enemy, transformComponent);

    _registry.emplace<SceneComponent>(enemy, GameScenes::InGame);
    return enemy;
}

entt::entity EntityFactory::createEnemyProjectile(
    entt::entity hint, std::pair<float, float> position
)
{
    auto projectile = _registry.create(hint);
    auto texture = _resourceManager.loadTexture(_assetsPath + "/bydos/enemy_shot.png");
    sf::IntRect initialFrameRect(0, 0, 7, 6);

    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(position.first, position.second));
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(2.0f, 2.0f));
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    sf::Vector2f scaledSize = sf::Vector2f(7.0f, 6.0f) * 2.0f;
    renderable.sprite.setOrigin(scaledSize.x / 2.0f, scaledSize.y / 2.0f);
    _registry.emplace<RenderableComponent>(projectile, std::move(renderable));

    TransformComponent transformComponent = {
        .x = position.first,
        .y = position.second,
        .scaleX = 2.0f,
        .scaleY = 2.0f,
        .width = 7,
        .height = 6,
    };
    _registry.emplace<TransformComponent>(projectile, transformComponent);

    _registry.emplace<SceneComponent>(projectile, GameScenes::InGame);
    _registry.emplace<InfiniteAnimationComponent>(projectile, 4, 0.25f);
    return projectile;
}

entt::entity EntityFactory::createExplosion(std::pair<float, float> position)
{
    auto explosion = _registry.create();
    auto texture = _resourceManager.loadTexture(_assetsPath + "/explosions/ships_explosions.png");
    sf::IntRect initialFrameRect(0, 0, 256, 256);
    
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(position.first, position.second));
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(0.75f, 0.75f));
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    sf::Vector2f scaledSize = sf::Vector2f(265.0f, 256.0f) * 0.75f;
    renderable.sprite.setOrigin(scaledSize.x / 2.0f, scaledSize.y / 2.0f);
    _registry.emplace<RenderableComponent>(explosion, std::move(renderable));

    TransformComponent transformComponent = {
        .x = position.first,
        .y = position.second,
        .scaleX = 0.75f,
        .scaleY = 0.75f,
        .width = 256,
        .height = 256,
    };
    _registry.emplace<TransformComponent>(explosion, transformComponent);

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
    _registry.emplace<TransformComponent>(background, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0);
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
        1.0f, 1.0f, 0, 0);
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
    _registry.emplace<TransformComponent>(planet, x, y, 1.0f, 1.0f, 0, 0);
    _registry.emplace<PlanetComponent>(planet);
    _registry.emplace<SceneComponent>(planet);
    _registry.emplace<InfiniteAnimationComponent>(planet, 256, 8.6f);
    return planet;
}

entt::entity EntityFactory::createHealth() {
    auto health = _registry.create();
    auto texture = _resourceManager.loadTexture(_assetsPath + "/player/heart.png");

    sf::IntRect initialFrameRect(0, 0, 3068, 3068);
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(100.0f, 1820.0f));
    renderable.sprite.setTexture(*texture);
    renderable.sprite.setScale(sf::Vector2f(0.03f, 0.03f));
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    _registry.emplace<RenderableComponent>(health, std::move(renderable));

    _registry.emplace<TransformComponent>(health, 100.0f, WINDOW_HEIGHT - 3068.0f / 26, 0.03f, 0.03f, 3068, 3068);
    _registry.emplace<SceneComponent>(health, GameScenes::InGame);
    _registry.emplace<HealthComponent>(health, 3.0f);
    return health;
}