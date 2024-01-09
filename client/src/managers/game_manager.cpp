#include "../../include/managers/game_manager.hpp"

#include "../../include/utils.hpp"

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

    std::queue<rtype::Event> messages;
    std::mutex messages_mutex;

    boost::asio::io_context io_context;
    ClientUDP client(io_context, _server_ip, _server_port);

    std::thread client_thread([&io_context, &client, &messages, &messages_mutex]() {
        while (true) {
            io_context.poll();  // Handle asynchronous operations

            // Check for stop request
            if (client.stop_requested_) {
                std::cout << "Stopping client thread..." << std::endl;
                rtype::Event event;
                event.set_event(rtype::EventType::QUIT);
                client.send_payload(event);
                break;
            }

            // Send messages to the server
            {
                std::lock_guard<std::mutex> lock(messages_mutex);
                while (!messages.empty()) {
                    client.send_payload(messages.front());
                    messages.pop();
                }
            }
        }
    });

    game_loop(messages, messages_mutex, client);
    client.stop();
    client_thread.join();
}

void GameManager::game_loop(
    std::queue<rtype::Event>& messages, std::mutex& messages_mutex, ClientUDP& client
)
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
    musicSound.sound.play();

    int wave = 0;
    while (_window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
            if (isInputEvent(event)) {
                _inputManager.processKeyPress(event);
                _inputManager.processKeyRelease(event);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                sound.playSound();

                entt::entity player = _playerProfileManager.getPlayerEntity();
                const sf::Vector2f& playerPosition =
                    _registry.get<RenderableComponent>(player).sprite.getPosition();
                _entityFactory.createProjectile(
                    1.0f, 0.0f, playerPosition.x + 145.0f, playerPosition.y + 47.5f, 25.0f
                );
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                _sceneManager.setCurrentScene(GameScenes::InGame);
            }
        }
        if (musicSound.sound.getStatus() == sf::Music::Stopped) {
            musicSound.sound.play();
        }
        auto payloads = client.get_payloads();
        for (auto payload : payloads) {

            // std::cout << "Payload : " << payload.ShortDebugString() << std::endl;
            if (_playerPresent.find(payload.identity()) == _playerPresent.end()) {
                printf(
                    "Player %u joined the game\n", static_cast<unsigned int>(payload.identity())
                );
                _playerPresent.insert(payload.identity());

                entt::entity player = static_cast<entt::entity>(payload.identity());
                auto playerEntity = _entityFactory.createPlayer(player);
                if (_isFirstPlayer) {
                    _playerProfileManager.setPlayerEntity(playerEntity);
                    _isFirstPlayer = false;
                }
            }
            if (!_playerPresent.empty()) {
                // Update player position
                std::lock_guard<std::mutex> lock(messages_mutex);
                processPlayerActions(deltaTime.asSeconds(), messages);
                entt::entity playerEntity = static_cast<entt::entity>(payload.identity());

                auto& transform = _registry.get<TransformComponent>(playerEntity);
                transform.x = payload.posx();
                transform.y = payload.posy();

                if (enemyClock.getElapsedTime().asSeconds() > 0.5f) {
                    enemyClock.restart();
                    float randomSpeed = getRandomFloat(2.0f, 5.0f);
                    float randomY = getRandomFloat(0.0f, WINDOW_HEIGHT - 64.0f);
                    float randomX = getRandomFloat(0.0f, WINDOW_WIDTH - 64);
                    _entityFactory.createNormalEnemy(randomY, randomSpeed);
                    _entityFactory.createFastEnemy(randomX, 10.0f);
                }
            }
        }
        if (transitionClock.getElapsedTime().asSeconds() > 5.0f) {
            transitionClock.restart();
            //_entityFactory.createWaveTransition("wave " + std::to_string(wave));
            makeEnemyShoot();
            wave++;
        }
        _window.clear();
        parallaxSystem(deltaTime.asSeconds());
        planetSystem(deltaTime.asSeconds());
        if (!_playerPresent.empty()) {
            renderSystem();
            enemySystem(explosionSound.sound);
            velocitySystem();
            collisionProjectileAndEnemy();
            makeAllAnimations();
        }
        _window.display();
    }
};
