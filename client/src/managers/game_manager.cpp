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
    _window.setFramerateLimit(60);
    std::cout << "GameManager created!" << std::endl;
}

void GameManager::start_game()
{
    _entityFactory.createMainMenu();

    _entityFactory.createPlanet(
        WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "/background/layer_1/wet_256.png"
    );
    _entityFactory.createPlanet(
        WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 300, "/background/layer_1/ice_256.png"
    );
    _entityFactory.createBackground();

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
    auto soundBuffer = _resourceManager.loadSoundBuffer(_assetsPath + "/sound_fx/shot2.wav");
    auto explosionSoundBuffer =
        _resourceManager.loadSoundBuffer(_assetsPath + "/sound_fx/explosion.wav");
    auto musicSoundBuffer = _resourceManager.loadSoundBuffer(_assetsPath + "/sound_fx/music.wav");

    SoundComponent sound(*soundBuffer);
    sound.setVolumeLevel(1.5f);
    SoundComponent explosionSound(*explosionSoundBuffer);
    explosionSound.setVolumeLevel(7.5f);
    SoundComponent musicSound(*musicSoundBuffer);
    musicSound.setVolumeLevel(2.0f);
    musicSound.sound.setLoop(true);
    musicSound.sound.play();

    int wave = 0;
    while (_window.isOpen()) {
        sf::Time deltaTime = clock.restart();
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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                // sound.playSound(); // TODO : play song only when GameScenes::InGame

                // TODO : handle key to send to the server as rtype::Event in the rtype::Payload
                // entt::entity player = _playerProfileManager.getPlayerEntity();
                // const sf::Vector2f& playerPosition =
                //     _registry.get<RenderableComponent>(player).sprite.getPosition();
                // _entityFactory.createProjectile(
                //     1.0f, 0.0f, playerPosition.x + 145.0f, playerPosition.y + 47.5f, 5.0f
                // );
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
                rtype::Connect connect_message;
                connect_message.set_player_name("Player Kevin");

                rtype::Payload payload;
                payload.mutable_connect()->CopyFrom(connect_message);

                _networkManager.send(payload);
            }
        }
        // if (transitionClock.getElapsedTime().asSeconds() > 5.0f) {
        //     transitionClock.restart();
        //     //_entityFactory.createWaveTransition("wave " + std::to_string(wave));
        //     // makeEnemyShoot();
        //     wave++;
        // }
        _window.clear();

        processServerResponse();
        if (!_connectedPlayerIds.empty()) {
            processPlayerActions(deltaTime.asSeconds());

            //         if (enemyClock.getElapsedTime().asSeconds() > 0.5f) {
            //             enemyClock.restart();
            //             float randomSpeed = getRandomFloat(2.0f, 5.0f);
            //             float randomY = getRandomFloat(0.0f, WINDOW_HEIGHT - 64.0f);
            //             _entityFactory.createNormalEnemy(randomY, randomSpeed);
            //         }
            //     }
        }
        planetSystem(deltaTime.asSeconds());
        parallaxSystem(deltaTime.asSeconds());
        renderSystem();
        makeAllAnimations();

        _window.display();
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
        std::cout << RED << "MOVE SHOOT" << RESET << std::endl;
        send_event_to_server(rtype::EventType::SHOOT);
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
        entt::entity player = static_cast<entt::entity>(payload.connect_response().player_id());
        auto playerEntity = _entityFactory.createPlayer(player);
        _connectedPlayerIds.insert(payload.connect_response().player_id());

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
    for (const auto& playerState : game_state.players()) {
        // TODO : should maybe check with my set of uint32_t if the player is already connected
        uint32_t playerID = playerState.player_id();
        float posX = playerState.pos_x();
        float posY = playerState.pos_y();
        float health = playerState.health();
        bool isShooting = playerState.is_shooting();

        std::cout << MAGENTA << "Player " << playerID << ": Position(" << posX << ", " << posY
                  << "), Health: " << health << ", IsShooting: " << (isShooting ? "Yes" : "No")
                  << RESET << std::endl;

        entt::entity playerEntity = static_cast<entt::entity>(playerID);

        const bool isPlayerAlreadyExist = _connectedPlayerIds.contains(playerID);
        if (!isPlayerAlreadyExist) {
            _entityFactory.createPlayer(playerEntity);
            _connectedPlayerIds.insert(playerID);
        }

        if (_registry
                .all_of<TransformComponent, HealthComponent, ScoreComponent, RenderableComponent>(
                    playerEntity
                )) {
            auto& transformComponent = _registry.get<TransformComponent>(playerEntity);
            auto& healthComponent = _registry.get<HealthComponent>(playerEntity);
            auto& scoreComponent = _registry.get<ScoreComponent>(playerEntity);
            auto& renderableComponent = _registry.get<RenderableComponent>(playerEntity);

            transformComponent.x = posX;
            transformComponent.y = posY;

            healthComponent.healthPoints = health;

            renderableComponent.sprite.setPosition(posX, posY);
        } else {
            std::cerr << "update_player_state() << Entity with ID " << playerID
                      << " does not have required components." << std::endl;
        }
    }
}

void GameManager::update_game_wave(const rtype::GameState& game_state)
{
    if (game_state.has_wave_state()) {
        const rtype::WaveState& gameWave = game_state.wave_state();

        _currentWaveLevel = gameWave.current_wave();
        _numberOfWaveEnemies = gameWave.total_enemies();
        _isWaveInProgress = gameWave.wave_in_progress();

        std::cout << "Wave Info: Current Wave: " << _currentWaveLevel
                  << ", Total Enemies: " << _numberOfWaveEnemies
                  << ", Wave In Progress: " << (_isWaveInProgress ? "Yes" : "No") << std::endl;

        if (_isWaveInProgress) {
            if (_enemiesIds.size() < _numberOfWaveEnemies) {
                for (const auto& enemyState : game_state.enemies()) {
                    const bool isIdAlreadyPresent =
                        _enemiesIds.contains(enemyState.enemy_id());  // ! C++20

                    std::cout << "isIdAlreadyPresent: " << isIdAlreadyPresent << std::endl;
                    if (!isIdAlreadyPresent) {
                        uint32_t enemyID = enemyState.enemy_id();
                        float posX = enemyState.pos_x();
                        float posY = enemyState.pos_y();
                        rtype::EnemyType type = enemyState.type();
                        float health = enemyState.health();

                        std::cout << "Enemy " << enemyID << ": Type(" << type << "), Position("
                                  << posX << ", " << posY << "), Health: " << health << std::endl;

                        entt::entity enemyEntity = static_cast<entt::entity>(enemyID);

                        if (_registry.all_of<TransformComponent, HealthComponent>(enemyEntity)) {
                            auto& transformComponent =
                                _registry.get<TransformComponent>(enemyEntity);
                            auto& healthComponent = _registry.get<HealthComponent>(enemyEntity);

                            transformComponent.x = posX;
                            transformComponent.y = posY;

                            healthComponent.healthPoints = health;

                        } else {
                            std::cerr << "Enemy entity with ID " << enemyID
                                      << " does not have required components." << std::endl;
                        }
                    }
                }
            } else {
                std::cout << "No enemies to create" << std::endl;
            }
        }
    } else {
        std::cerr << "Wave not in progress or no wave info." << std::endl;
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
        // update_player_score(gameState);
        // update_enemies_state(gameState);
        // update_game_wave(gameState);
        // TODO : Continue for powerUps, scores, bullets, etc.
    } else {
        std::cerr << "Payload does not contain a GameState." << std::endl;
    }
}
