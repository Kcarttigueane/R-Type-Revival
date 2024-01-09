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

    std::thread io_thread([&]() { _io_service.run(); });

    game_loop();
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
                _window.close();
            }
            if (isInputEvent(event)) {
                // TODO : handle key to send to the server as rtype::Event in the rtype::Payload
                // std::lock_guard<std::mutex> lock(messages_mutex);
                // messages.push(handle_key(event.key.code));
                _inputManager.processKeyPress(event);
                _inputManager.processKeyRelease(event);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                sound.playSound();

                // TODO : handle key to send to the server as rtype::Event in the rtype::Payload
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
                rtype::Connect connect_message;
                connect_message.set_player_name("Player Kevin");

                rtype::Payload payload;
                payload.mutable_connect()->CopyFrom(connect_message);

                _networkManager.send(payload);
            }

            processServerResponse();

            //     if (!_playerPresent.empty()) {
            //         processPlayerActions(deltaTime.asSeconds());
            //         // Update player position
            //         entt::entity playerEntity = static_cast<entt::entity>(payload.identity());

            //         auto& transform = _registry.get<TransformComponent>(playerEntity);
            //         transform.x = payload.posx();
            //         transform.y = payload.posy();

            //         if (enemyClock.getElapsedTime().asSeconds() > 0.5f) {
            //             enemyClock.restart();
            //             float randomSpeed = getRandomFloat(2.0f, 5.0f);
            //             float randomY = getRandomFloat(0.0f, WINDOW_HEIGHT - 64.0f);
            //             _entityFactory.createNormalEnemy(randomY, randomSpeed);
            //         }
            //     }
            // }

            _window.clear();

            if (_connectedPlayerIds.empty()) {
                parallaxSystem(deltaTime.asSeconds());
                planetSystem(deltaTime.asSeconds());
                // enemySystem(explosionSound.sound);
                // renderSystem();
                // projectileSystem();
                // collisionProjectileAndEnemy(); // TODO : to put in the server
                // collisionEnemyAndPlayer(); // TODO : to put in the server
                // makeAllAnimations();
            }

            _window.display();
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
