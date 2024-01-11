#if !defined(GAME_MANGER_HPP)
#    define GAME_MANGER_HPP

#    include <thread>

#    include "../game_metadata.hpp"
#    include "./entity_manager.hpp"
#    include "./network_manager.hpp"
#    include "./players_session_manager.hpp"

#    include "../../../common/utils/id_generator.hpp"

#    include <chrono>

struct Wave {
    int number;
    std::vector<rtype::EnemyType> enemies;
    bool isActive;
    float duration;

    Wave(int num, float dur) : number(num), isActive(false), duration(dur) {}
};

class GameManager {
private:
    boost::asio::io_context _io_context;
    // std::thread _network_thread;
    std::jthread _network_thread;

    // ! Game metadata
    GameMetadata _game_metadata;

    // ! Managers
    EntityManager _entity_manager;
    NetworkManager _network_manager;

    // ! ID generator
    IdGenerator _idGenerator;

    // ! Wave management
    std::vector<Wave> _waves;
    int _currentWaveIndex;
    float _waveTimer;

    float getRandomFloat(float min, float max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distribution(min, max);
        return distribution(gen);
    }

    void initializeWaves()
    {
        Wave wave1(1, 20.0f);
        for (int i = 0; i < 2; ++i) {
            wave1.enemies.push_back(rtype::EnemyType::NORMAL);
        }
        for (int i = 0; i < 2; ++i) {
            wave1.enemies.push_back(rtype::EnemyType::FAST);
        }
        _waves.push_back(wave1);

        Wave wave2(2, 45.0f);
        for (int i = 0; i < 2; ++i) {
            wave2.enemies.push_back(rtype::EnemyType::NORMAL);
        }
        for (int i = 0; i < 2; ++i) {
            wave2.enemies.push_back(rtype::EnemyType::FAST);
        }
        _waves.push_back(wave2);

        Wave wave3(3, 60.0f);
        for (int i = 0; i < 2; ++i) {
            wave3.enemies.push_back(rtype::EnemyType::NORMAL);
        }
        for (int i = 0; i < 2; ++i) {
            wave3.enemies.push_back(rtype::EnemyType::FAST);
        }
        wave3.enemies.push_back(rtype::EnemyType::BOSS);
        _waves.push_back(wave3);

        _currentWaveIndex = 0;
        _waveTimer = 0.0f;
    }

    void startWave(Wave& wave)
    {
        if (!wave.isActive) {
            wave.isActive = true;

            for (const auto& enemyType : wave.enemies) {
                spawnEnemy(enemyType);
            }
        }
    }

    void updateWaves(float deltaTime)
    {
        if (_currentWaveIndex < _waves.size()) {
            Wave& currentWave = _waves[_currentWaveIndex];
            std::cout << "Wave " << currentWave.number << " is active: " << currentWave.isActive
                      << std::endl;
            std::cout << "Wave active: " << currentWave.isActive << std::endl;

            if (!currentWave.isActive) {
                startWave(currentWave);
            } else {
                _waveTimer += deltaTime;
                std::cout << "Wave " << currentWave.number << " timer: " << _waveTimer << std::endl;

                if (_waveTimer >= currentWave.duration) {
                    std::cout << "Ending wave " << currentWave.number << std::endl;
                    endWave(currentWave);
                    _waveTimer = 0.0f;
                    _currentWaveIndex++;
                }
            }
        }
    }

    void spawnEnemy(rtype::EnemyType enemyType)
    {
        std::uint32_t newEnemyId = _idGenerator.generateId();
        entt::entity playerEntityId = static_cast<entt::entity>(newEnemyId);

        switch (enemyType) {
            case rtype::EnemyType::NORMAL: {
                float randomNormalY = getRandomFloat(0.0f, WINDOW_HEIGHT - 64.0f);
                float randomNormalSpeed = getRandomFloat(2.0f, 5.0f);
                _entity_manager.createNormalEnemy(playerEntityId, randomNormalY, randomNormalSpeed);
                break;
            }
            case rtype::EnemyType::FAST: {
                float randomFastY = getRandomFloat(0.0f, WINDOW_HEIGHT - 64.0f);
                float randomFastSpeed = getRandomFloat(2.0f, 5.0f);
                _entity_manager.createFastEnemy(playerEntityId, randomFastY, randomFastSpeed);
                break;
            }
            case rtype::EnemyType::BOSS:
                // TODO : Implement boss enemy
                break;
            default:
                break;
        }
    }

    void endWave(Wave& wave)
    {
        wave.isActive = false;

        auto view = _entity_manager.getRegistry().view<EnemyComponent>();

        for (auto entity : view) {
            _entity_manager.getRegistry().destroy(entity);
        }
    }

public:
    GameManager(const std::string& server_address, std::string port);

    ~GameManager();

    void run();

    void game_loop();

    void updateGameLogic(float deltaTime) { updateWaves(deltaTime); }
};

#endif  // GAME_MANGER_HPP
