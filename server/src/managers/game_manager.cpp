#include "../../include/managers/game_manager.hpp"

GameManager::GameManager(const std::string& server_address, std::string port)
    : _network_manager(_io_context, port, _entity_manager, _idGenerator)
{}

GameManager::~GameManager()
{
    if (_network_thread.joinable()) {
        _io_context.stop();
    }
}

void GameManager::run()
{
    // _network_thread = std::thread([this]() { _io_context.run(); });
    _network_thread = std::jthread([this]() { _io_context.run(); });
    game_loop();
}

void GameManager::game_loop()
{
    while (_game_metadata.isRunning) {
        // TODO : Deal with game updates

        static auto last_update = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        if (now - last_update >= std::chrono::milliseconds(UPDATE_INTERVAL_MS)) {
            _network_manager.broadcast_game_state();
            last_update = now;
        }

        // TODO : Deal with game process -> enemies creations
    }
}
