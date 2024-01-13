#include "../../include/managers/game_manager.hpp"

#include "../../include/utils.hpp"

GameManager::GameManager(
    std::string server_ip, std::string server_port, boost::asio::io_service& io_service
)
    : _io_service(io_service),
      _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Type-Revival"),
      _inputManager(_registry, _window),
      _networkManager(io_service, server_ip, server_port),
      _playerProfileManager(),
      _resourceManager(),
      _sceneManager(_inputManager),
      _settingsManager(_resourceManager),
      _entityFactory(_registry, _resourceManager, _window)
{
    std::cout << "GameManager created!" << std::endl;

    _shootingSound =
        SoundComponent(*_resourceManager.loadSoundBuffer(_assetsPath + "/sound_fx/shot2.wav"));
    _explosionSound =
        SoundComponent(*_resourceManager.loadSoundBuffer(_assetsPath + "/sound_fx/explosion.wav"));
    _musicSound =
        SoundComponent(*_resourceManager.loadSoundBuffer(_assetsPath + "/sound_fx/music.wav"));
    _shootingSound.setVolumeLevel(1.5f);
    _explosionSound.setVolumeLevel(7.5f);
    _musicSound.setVolumeLevel(2.0f);
    _musicSound.sound.setLoop(true);
    _musicSound.sound.play();
}

void GameManager::start_game()
{
    entt::entity backgroundEntityId = static_cast<entt::entity>(BACKGROUND_ID);
    entt::entity MainMenuId = static_cast<entt::entity>(MAIN_MENU_ID);
    entt::entity PlaneWetId = static_cast<entt::entity>(PLANET_WET_ID);
    entt::entity PlaneIceId = static_cast<entt::entity>(PLANET_ICE_ID);
    entt::entity HealthId = static_cast<entt::entity>(HEALTH_ID);

    _entityFactory.createMainMenu(MainMenuId);
    _entityFactory.createPlanet(
        PlaneWetId, std::make_pair(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
        "/background/layer_1/wet_256.png"
    );
    _entityFactory.createPlanet(
        PlaneIceId, std::make_pair(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 300),
        "/background/layer_1/ice_256.png"
    );
    _entityFactory.createBackground(backgroundEntityId);
    _entityFactory.createHealth(HealthId);

    _network_thread = std::jthread([&]() { _io_service.run(); });
    game_loop();
}

void GameManager::handle_closing_game()
{
    rtype::Payload payload;
    rtype::Event* event = payload.mutable_event();
    event->set_event(rtype::EventType::QUIT);

    _networkManager.send(payload);

    if (_network_thread.joinable()) {
        _io_service.stop();
    }

    _registry.clear();
    _window.close();
}

void GameManager::game_loop()
{
    while (_window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        if (!_connectedPlayerIds.empty()) {
            processPlayerActions(deltaTime.asSeconds());
        }
        _window.clear();
        processServerResponse();
        planetSystem(deltaTime.asSeconds());
        parallaxSystem(deltaTime.asSeconds());
        renderSystem();
        makeAllAnimations();
        _window.display();
    }
}

void GameManager::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            handle_closing_game();
        }
        if (_sceneManager.getCurrentScene() == GameScenes::MainMenu) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                handle_closing_game();
            }
        }
        if (isInputEvent(event)) {
            _inputManager.processKeyPress(event);
            _inputManager.processKeyRelease(event);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
            rtype::Connect connect_message;
            connect_message.set_player_name("Player Kevin");
            rtype::Payload payload;
            payload.mutable_connect()->CopyFrom(connect_message);
            _networkManager.send(payload);
        }
    }
}

bool GameManager::isInputEvent(const sf::Event& event)
{
    // TODO: Add more input events if needed define scope with gars
    return event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased ||
           event.type == sf::Event::MouseButtonPressed ||
           event.type == sf::Event::MouseButtonReleased;
}

void GameManager::deleteAIEnemies()
{
    auto enemies = _registry.view<EnemyComponent>();
    for (auto enemy : enemies) {
        _registry.destroy(enemy);
    }
}

void GameManager::send_event_to_server(rtype::EventType event_type)
{
    rtype::Event event;
    event.set_event(event_type);

    rtype::Payload payload;
    payload.mutable_event()->CopyFrom(event);

    _networkManager.send(payload);
}

void GameManager::processPlayerActions(float deltaTime)
{
    auto& actions = _inputManager.getKeyboardActions();
    rtype::Event event;
    if (sendEventClock.getElapsedTime().asSeconds() >= INPUT_LIMITER) {
        if (actions.Up == true) {
            std::cout << RED << "MOVE UP" << RESET << std::endl;
            send_event_to_server(rtype::EventType::MOVE_UP);
        }
        if (actions.Down == true) {
            std::cout << RED << "MOVE DOWN" << RESET << std::endl;
            send_event_to_server(rtype::EventType::MOVE_DOWN);
        }
        if (actions.Right == true) {
            std::cout << RED << "MOVE RIGHT" << RESET << std::endl;
            send_event_to_server(rtype::EventType::MOVE_RIGHT);
        }
        if (actions.Left == true) {
            std::cout << RED << "MOVE LEFT" << RESET << std::endl;
            send_event_to_server(rtype::EventType::MOVE_LEFT);
        }
        if (actions.Shoot == true) {
            if (shootClock.getElapsedTime().asSeconds() >= SHOOT_LIMITER) {
                std::cout << RED << "MOVE SHOOT" << RESET << std::endl;
                send_event_to_server(rtype::EventType::SHOOT);
                shootClock.restart();
            }
        }
        sendEventClock.restart();
    }
}

void GameManager::processServerResponse()
{
    std::queue<rtype::Payload> messages = _networkManager.getReceivedMessages();

    while (!messages.empty()) {
        rtype::Payload payload = messages.front();
        processPayload(payload);
        messages.pop();
    }
}

void GameManager::processPayload(const rtype::Payload& payload)
{
    std::cout << "Processing payload" << payload.DebugString() << std::endl;

    if (payload.has_connect_response()) {
        handleConnectResponse(payload);
    } else if (payload.has_game_state()) {
        handleGameState(payload);
    } else {
        std::cerr << "Unknown payload type received." << std::endl;
    }
}

void GameManager::handleConnectResponse(const rtype::Payload& payload)
{
    std::cout << "Connect response -> player Id: " << payload.connect_response().player_id()
              << std::endl;
    std::cout << "Connect response -> Status " << payload.connect_response().status() << std::endl;

    rtype::ConnectResponseStatus responseStatus = payload.connect_response().status();

    if (responseStatus == rtype::ConnectResponseStatus::SUCCESS) {
        std::cout << "Connect response -> OK" << std::endl;
        // TODO : should I check if the set can container max 4 players
        _playerProfileManager.setPlayerEntity(
            static_cast<entt::entity>(payload.connect_response().player_id())
        );
        _sceneManager.setCurrentScene(GameScenes::InGame);
    } else if (responseStatus == rtype::ConnectResponseStatus::SERVER_FULL) {
        std::cout << "Connect response  -> KO" << std::endl;
        // TODO: Need to check how we handle this -> user experience
        return;
    } else {
        std::cout << "Connect response -> Unknown" << std::endl;
    }
}

void GameManager::update_player_state(const rtype::GameState& game_state)
{
    std::set<std::uint32_t> currentIds;

    for (const auto& playerState : game_state.players()) {
        // TODO : should maybe check with my set of uint32_t if the player is already connected
        uint32_t playerID = playerState.player_id();
        float posX = playerState.pos_x();
        float posY = playerState.pos_y();
        float health = playerState.health();

        std::cout << MAGENTA << "Player " << playerID << ": Position(" << posX << ", " << posY
                  << ")" << RESET << std::endl;

        entt::entity playerEntity = static_cast<entt::entity>(playerID);
        currentIds.insert(playerID);

        if (playerID == static_cast<std::uint32_t>(_playerProfileManager.getPlayerEntity())) {
            _playerProfileManager.setPlayerHealth(health);
            std::cout << "Profile Player health updated for player " << playerID << std::endl;
        }

        const bool isPlayerAlreadyExist = _connectedPlayerIds.contains(playerID);
        if (!isPlayerAlreadyExist) {
            _entityFactory.createPlayer(playerEntity, std::make_pair(posX, posY));
            _connectedPlayerIds.insert(playerID);
        }

        if (_registry.all_of<TransformComponent, RenderableComponent>(playerEntity)) {
            auto& transformComponent = _registry.get<TransformComponent>(playerEntity);
            auto& renderableComponent = _registry.get<RenderableComponent>(playerEntity);

            transformComponent.x = posX;
            transformComponent.y = posY;

            renderableComponent.sprite.setPosition(posX, posY);
        } else {
            std::cerr << "update_player_state() << Entity with ID " << playerID
                      << " does not have required components." << std::endl;
        }
    }

    for (auto it = _connectedPlayerIds.begin(); it != _connectedPlayerIds.end();) {
        std::uint32_t id = *it;
        if (!currentIds.contains(id)) {
            if (_registry.valid(static_cast<entt::entity>(id))) {
                TransformComponent& transformable =
                    _registry.get<TransformComponent>(static_cast<entt::entity>(id));
                _entityFactory.createExplosion(std::make_pair(transformable.x, transformable.y));
                _registry.destroy(static_cast<entt::entity>(id));
            }
            it = _connectedPlayerIds.erase(it);
        } else {
            ++it;
        }
    }
}

void GameManager::updateBulletState(const rtype::GameState& game_state)
{
    std::set<std::uint32_t> currentIds;

    for (const auto& bulletState : game_state.bullets()) {
        std::uint32_t bulletID = bulletState.bullet_id();
        float posX = bulletState.pos_x();
        float posY = bulletState.pos_y();
        std::uint32_t ownerID = bulletState.owner_id();

        std::cout << MAGENTA << "Bullet " << bulletID << RESET << std::endl;

        entt::entity bulletEntity = static_cast<entt::entity>(bulletID);
        currentIds.insert(bulletID);

        if (!_bulletIds.contains(bulletID)) {
            if (_connectedPlayerIds.contains(ownerID)) {
                _entityFactory.createProjectile(bulletEntity, std::make_pair(posX, posY));
            } else {
                _entityFactory.createEnemyProjectile(bulletEntity, std::make_pair(posX, posY));
            }
            _bulletIds.insert(bulletID);
        }

        if (_registry.all_of<TransformComponent, RenderableComponent>(bulletEntity)) {
            TransformComponent& transformable = _registry.get<TransformComponent>(bulletEntity);
            RenderableComponent& renderable = _registry.get<RenderableComponent>(bulletEntity);

            transformable.x = posX;
            transformable.y = posY;

            renderable.sprite.setPosition(sf::Vector2f(transformable.x, transformable.y));
        } else {
            std::cerr << "updateBulletState() << Entity with ID " << bulletID
                      << " does not have required components." << std::endl;
        }
    }

    for (auto it = _bulletIds.begin(); it != _bulletIds.end();) {
        std::uint32_t id = *it;
        if (!currentIds.contains(id)) {
            if (_registry.valid(static_cast<entt::entity>(id))) {
                _registry.destroy(static_cast<entt::entity>(id));
            }
            it = _bulletIds.erase(it);
        } else {
            ++it;
        }
    }
}

void GameManager::update_game_wave(const rtype::GameState& game_state)
{
    if (game_state.has_wave_state()) {
        const rtype::WaveState& gameWave = game_state.wave_state();

        _currentWaveLevel = gameWave.current_wave();
        _isWaveInProgress = gameWave.is_wave_in_progress();

        std::cout << "Wave Info: Current Wave: " << _currentWaveLevel
                  << ", Wave In Progress: " << (_isWaveInProgress ? "Yes" : "No") << std::endl;

        if (_isWaveInProgress) {
            for (const auto& enemyState : game_state.enemies()) {
                uint32_t enemyID = enemyState.enemy_id();
                float posX = enemyState.pos_x();
                float posY = enemyState.pos_y();
                rtype::EnemyType type = enemyState.type();
                float health = enemyState.health();  // Not needed for normal and fast enemies

                std::cout << "Enemy " << enemyID << ": Type(" << type << "), Position(" << posX
                          << ", " << posY << "), Health: " << health << std::endl;

                entt::entity enemyEntity = static_cast<entt::entity>(enemyID);

                const bool isIdAlreadyPresent = _enemiesIds.contains(enemyState.enemy_id());

                std::cout << "isIdAlreadyPresent: " << isIdAlreadyPresent << std::endl;
                if (!isIdAlreadyPresent) {
                    std::cout << "la vie est belle" << std::endl;
                    entt::entity enemyEntity = static_cast<entt::entity>(enemyID);
                    _enemiesIds.insert(enemyID);
                    _entityFactory.createEnemy(type, enemyEntity, std::make_pair(posX, posY));
                }

                if (_registry.all_of<TransformComponent, RenderableComponent>(enemyEntity)) {
                    auto& transformComponent = _registry.get<TransformComponent>(enemyEntity);
                    auto& renderableComponent = _registry.get<RenderableComponent>(enemyEntity);

                    transformComponent.x = posX;
                    transformComponent.y = posY;

                    renderableComponent.sprite.setPosition(posX, posY);
                } else {
                    std::cerr << "Enemy entity with ID " << enemyID
                              << " does not have required components." << std::endl;
                }
            }
        } else {
            std::cerr << "Wave not in progress or no wave info." << std::endl;
        }
    }
}

void GameManager::update_player_score(const rtype::GameState& game_state)
{
    for (const auto& playerScore : game_state.scores()) {
        uint32_t playerID = playerScore.player_id();
        uint32_t score = playerScore.score();

        std::cout << "Player " << playerID << ": Score: " << score << std::endl;

        entt::entity playerEntity = static_cast<entt::entity>(playerID);

        if (_registry.all_of<ScoreComponent>(playerEntity)) {
            auto& scoreComponent = _registry.get<ScoreComponent>(playerEntity);

            scoreComponent.score = score;

        } else {
            std::cerr << "Entity with ID " << playerID << " does not have required components."
                      << std::endl;
        }
    }
}

void GameManager::handleGameState(const rtype::Payload& payload)
{
    if (payload.has_game_state()) {
        const rtype::GameState& gameState = payload.game_state();

        update_player_state(gameState);
        updateBulletState(gameState);
        // update_player_score(gameState);
        // update_enemies_state(gameState);
        update_game_wave(gameState);
    } else {
        std::cerr << "Payload does not contain a GameState." << std::endl;
    }
}
