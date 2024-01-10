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
    _entityFactory.createWinScene();
    _entityFactory.createLoseScene();

    _entityFactory.createPlanet(
        WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "/background/layer_1/wet_256.png"
    );
    _entityFactory.createPlanet(
        WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 300, "/background/layer_1/ice_256.png"
    );
    _entityFactory.createBackground();

    // std::thread io_thread([&]() { _io_service.run(); });
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

            processServerResponse();
        }
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

        _window.clear();

        planetSystem(deltaTime.asSeconds());
        parallaxSystem(deltaTime.asSeconds());
        renderSystem();
        makeAllAnimations();

        // if (!_connectedPlayerIds.empty()) {
        //     std::cout << MAGENTA << "PLAYERS IN THE GAME" << RESET << std::endl;
        //     // enemySystem(explosionSound.sound);
        //     // projectileSystem();
        // }

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
    auto enemies = _registry.view<EnemyAIComponent>();
    for (auto enemy : enemies) {
        _registry.destroy(enemy);
    }
}

void GameManager::processPlayerActions(float deltaTime)
{
    auto& actions = _inputManager.getKeyboardActions();
    rtype::Event event;

    if (actions.Up == true) {

        rtype::Event event;
        event.set_event(rtype::EventType::MOVE_UP);

        rtype::Payload payload;
        payload.mutable_event()->CopyFrom(event);

        _networkManager.send(payload);
    }
    if (actions.Down == true) {
        event.set_event(rtype::EventType::MOVE_DOWN);

        rtype::Payload payload;
        payload.mutable_event()->CopyFrom(event);

        _networkManager.send(payload);
    }
    if (actions.Right == true) {
        event.set_event(rtype::EventType::MOVE_RIGHT);

        rtype::Payload payload;
        payload.mutable_event()->CopyFrom(event);

        _networkManager.send(payload);
    }
    if (actions.Left == true) {
        event.set_event(rtype::EventType::MOVE_LEFT);

        rtype::Payload payload;
        payload.mutable_event()->CopyFrom(event);

        _networkManager.send(payload);
    }
    if (actions.Shoot == true) {
        event.set_event(rtype::EventType::SHOOT);
        rtype::Payload payload;
        payload.mutable_event()->CopyFrom(event);

        _networkManager.send(payload);
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
