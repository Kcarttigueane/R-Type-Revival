#include "../include/entity_factory.hpp"

EntityFactory ::EntityFactory(
    entt::registry& registry, ResourceManager& resourceManager, sf::RenderWindow& window
)
    : _registry(registry), _resourceManager(resourceManager), _window(window){};

entt::entity EntityFactory::createPlayer(entt::entity hint, std::pair<float, float> position)
{
    auto player = _registry.create(hint);
    auto texture = _resourceManager.loadTexture(_assetsPath + "/bydos/bydos.png");
    sf::IntRect initialFrameRect(277, 44, 86, 40);
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setTexture(*texture);
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    renderable.sprite.setOrigin(86.0f / 2.0f, 40.0f / 2.0f);
    renderable.sprite.setScale(sf::Vector2f(2.0f, 2.0f));
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    renderable.text.setFont(*font);
    renderable.text.setString("Score : 0");
    renderable.text.setCharacterSize(50);
    renderable.text.setPosition(WINDOW_WIDTH - 450, 50);

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

entt::entity EntityFactory::createProjectile(entt::entity hint, std::pair<float, float> position)
{
    auto projectile = _registry.create(hint);
    auto texture = _resourceManager.loadTexture(_assetsPath + "/player/player_shots.png");
    sf::IntRect initialFrameRect(0, 0, 54, 12);

    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(position.first, position.second));
    renderable.sprite.setTexture(*texture);
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    renderable.sprite.setScale(sf::Vector2f(1.0f, 1.0f));
    renderable.sprite.setOrigin(48, 12 / 2.0f);
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

entt::entity EntityFactory::createNormalEnemy(entt::entity hint, std::pair<float, float> position)
{
    auto enemy = _registry.create(hint);
    auto texture = _resourceManager.loadTexture(_assetsPath + "/bydos/bydos.png");
    sf::IntRect initialFrameRect(32, 48, 64, 32);

    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(position.first, position.second));
    renderable.sprite.setTexture(*texture);
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    renderable.sprite.setOrigin(64.0f / 2.0f, 32.0f / 2.0f);
    renderable.sprite.setScale(sf::Vector2f(-2.0, 2.0));

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

entt::entity EntityFactory::createEnemy(
    rtype::EnemyType type, entt::entity hint, std::pair<float, float> position
)
{
    switch (type) {
        case rtype::EnemyType::NORMAL:
            return createNormalEnemy(hint, position);
        case rtype::EnemyType::FAST:
            return createFastEnemy(hint, position);
        case rtype::EnemyType::BOSS:
            // TODO: Implement boss enemy creation logic
            break;
        default:
            break;
    }
    return entt::null;
}

entt::entity EntityFactory::createFastEnemy(entt::entity hint, std::pair<float, float> position)
{
    auto enemy = _registry.create(hint);
    auto texture = _resourceManager.loadTexture(_assetsPath + "/bydos/bydos.png");
    sf::IntRect initialFrameRect(150, 48, 82, 32);

    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(position.first, position.second));
    renderable.sprite.setTexture(*texture);
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    renderable.sprite.setOrigin(82.0f / 2.0f, 32.0f / 2.0f);
    renderable.sprite.setScale(sf::Vector2f(2.0, 2.0));
    renderable.sprite.setRotation(90.0f);
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
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    renderable.sprite.setOrigin(7.0 / 2.0f, 6.0f / 2.0f);
    renderable.sprite.setScale(sf::Vector2f(2.0f, 2.0f));
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
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    renderable.sprite.setOrigin(256.0f / 2.0f, 256.0f / 2.0f);
    renderable.sprite.setScale(sf::Vector2f(0.75f, 0.75f));
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

entt::entity EntityFactory::createBackground(entt::entity hint)
{
    auto texture =
        _resourceManager.loadTexture(_assetsPath + "/background/layer_3/space_background.png");
    auto background = _registry.create(hint);
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

entt::entity EntityFactory::createWaveTransition(entt::entity hint, std::string title)
{
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    auto transitionTitle = _registry.create(hint);
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
        1.0f, 1.0f, 0, 0
    );
    _registry.emplace<VelocityComponent>(transitionTitle, -1.0f, 0.0f, 0.5f);
    _registry.emplace<RenderableComponent>(transitionTitle, std::move(renderable));
    _registry.emplace<SceneComponent>(transitionTitle, GameScenes::InGame);
    return transitionTitle;
}

entt::entity EntityFactory::createPlanet(
    entt::entity hint, std::pair<float, float> position, std::string randomFilepath
)
{
    auto planet = _registry.create(hint);
    auto texture = _resourceManager.loadTexture(_assetsPath + randomFilepath);

    sf::IntRect initialFrameRect(0, 0, 64, 64);
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(position.first, position.second));
    renderable.sprite.setTexture(*texture);
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    renderable.sprite.setOrigin(64.0f / 2.0f, 64.0f / 2.0f);
    renderable.sprite.setScale(sf::Vector2f(2.0f, 2.0f));
    _registry.emplace<RenderableComponent>(planet, std::move(renderable));
    _registry.emplace<TransformComponent>(
        planet, position.first, position.second, 1.0f, 1.0f, 0, 0
    );
    _registry.emplace<PlanetComponent>(planet);
    _registry.emplace<InfiniteAnimationComponent>(planet, 256, 8.6f);

    return planet;
}

entt::entity EntityFactory::createHealth(entt::entity hint)
{
    auto health = _registry.create(hint);
    auto texture = _resourceManager.loadTexture(_assetsPath + "/player/heart.png");

    sf::IntRect initialFrameRect(0, 0, 3068, 3068);
    RenderableComponent renderable;
    renderable.texture = texture;
    renderable.sprite.setPosition(sf::Vector2f(100.0f, 500.0f));
    renderable.sprite.setTexture(*texture);
    renderable.frameRect = initialFrameRect;
    renderable.sprite.setTextureRect(initialFrameRect);
    renderable.sprite.setScale(sf::Vector2f(0.03f, 0.03f));
    _registry.emplace<RenderableComponent>(health, std::move(renderable));

    _registry.emplace<TransformComponent>(
        health, 100.0f, WINDOW_HEIGHT - 3068.0f / 18, 0.03f, 0.03f, 3068, 3068
    );
    _registry.emplace<SceneComponent>(health, GameScenes::InGame);
    _registry.emplace<HealthComponent>(health, 3.0f);
    return health;
}

entt::entity EntityFactory::createMainMenuTitle(entt::entity hint)
{
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    auto mainMenuTitle = _registry.create(hint);

    RenderableComponent renderable;
    renderable.text.setFont(*font);
    renderable.text.setString(GAME_TITLE);
    renderable.text.setCharacterSize(96);
    sf::FloatRect titleBounds = renderable.text.getLocalBounds();
    renderable.text.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    renderable.text.setPosition(_window.getSize().x / 2, _window.getSize().y * 0.20);

    _registry.emplace<RenderableComponent>(mainMenuTitle, std::move(renderable));
    _registry.emplace<SceneComponent>(mainMenuTitle, GameScenes::MainMenu);

    return mainMenuTitle;
}

entt::entity EntityFactory::createButton(
    const std::string& path, const std::string& label, int index, bool isSelected,
    entt::entity buttonId
)
{
    auto button = _registry.create(buttonId);
    entt::entity PlaneWetId = static_cast<entt::entity>(123);
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

    TransformComponent transformComponent = {
        .x = buttonX,
        .y = buttonY,
        .scaleX = 1.0f,
        .scaleY = 1.0f,
        .width = 0,
        .height = 0,
    };

    _registry.emplace<TransformComponent>(button, transformComponent);

    return button;
}

entt::entity EntityFactory::createSelectedLabel(entt::entity hint)
{
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    auto labelEntity = _registry.create(hint);
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
    entt::entity hint, const std::string& settingName,
    const std::vector<std::string>& settingValues, int currentValueIndex, int index
)
{
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    auto settingsItem = _registry.create(hint);

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

entt::entity EntityFactory::createAboutMenu(entt::entity hint)
{
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    auto aboutMenuEntity = _registry.create(hint);
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

entt::entity EntityFactory::createTutorialPage(entt::entity hint)
{
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");
    auto tutorialPageEntity = _registry.create(hint);
    RenderableComponent renderable;

    std::string tutorialText =
        "Welcome to the R-Type 2 Tutorial!\n\n"
        "In this tutorial, we will guide you through the basics of the game.\n"
        "Follow these steps to get started:\n\n"
        "1. Move your ship using the arrow keys.\n"
        "2. Press the Spacebar to shoot.\n"
        "3. Dodge enemy attacks to stay alive.\n"
        "4. Collect power-ups to upgrade your ship.\n\n"
        "Have fun and save the galaxy!\n\n"
        "Good luck, Captain!";

    renderable.text.setFont(*font);
    renderable.text.setString(tutorialText);
    renderable.text.setCharacterSize(32);
    renderable.text.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = renderable.text.getLocalBounds();
    renderable.text.setOrigin(textBounds.width / 2, textBounds.height / 2);
    renderable.text.setPosition(_window.getSize().x / 2, _window.getSize().y * 0.50);

    _registry.emplace<RenderableComponent>(tutorialPageEntity, std::move(renderable));
    _registry.emplace<SceneComponent>(tutorialPageEntity, GameScenes::Tutorial);

    return tutorialPageEntity;
}

entt::entity EntityFactory::createTextEntity(
    entt::entity hint, const std::string& initialText, float x, float y
)
{
    auto lobbyEntity = _registry.create(hint);
    auto font = _resourceManager.loadFont(_assetsPath + "/fonts/francis.ttf");

    RenderableComponent renderable;
    renderable.text.setFont(*font);
    renderable.text.setString(initialText);
    renderable.text.setCharacterSize(32);
    renderable.text.setPosition(x, y);

    _registry.emplace<RenderableComponent>(lobbyEntity, std::move(renderable));
    _registry.emplace<SceneComponent>(lobbyEntity, GameScenes::Lobby);

    return lobbyEntity;
}
