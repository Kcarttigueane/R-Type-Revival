#include "../../include/managers/game_manager.hpp"

GameManager::GameManager(const std::string& server_address, std::string port)
    : _wave_manager(_entity_manager, _idGenerator),
      _network_manager(_io_context, port, _entity_manager, _wave_manager, _idGenerator)
{}

GameManager::~GameManager()
{
    if (_network_thread.joinable()) {
        _io_context.stop();
    }
}

void GameManager::run()
{
    _network_thread = std::jthread([this]() { _io_context.run(); });
    game_loop();
}

void GameManager::game_loop()
{
    using Clock = std::chrono::steady_clock;
    auto last_update = Clock::now();

    while (_game_metadata.isRunning) {
        auto now = Clock::now();
        float deltaTime =
            std::chrono::duration<float, std::chrono::seconds::period>(now - last_update).count();

        if (deltaTime >= UPDATE_INTERVAL_MS / 1000.0f) {
            updateGameLogic(deltaTime);
            _network_manager.broadcast_game_state();
            last_update = now;
            velocitySystem();
            collisionProjectileAndEnemy();
            deleteDeadEnemies();
            collisionPlayerAndEnemy();
            makeEnemyShoot();
            collisionPlayerAndEnemyBullet();
        }
    }
}

void GameManager::updateGameLogic(float deltaTime)
{
    entt::registry& registry = _entity_manager.getRegistry();

    auto view = registry.view<PlayerComponent>();

    if (view.size() == 0) {
        return;
    }

    _wave_manager.updateWaves(deltaTime);
}
