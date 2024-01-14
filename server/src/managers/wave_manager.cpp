#include "../../include/managers/wave_manager.hpp"

float WaveManager::getRandomFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}

WaveManager::WaveManager(EntityManager& entityManager, IdGenerator& idGenerator)
    : _entityManager(entityManager),
      _idGenerator(idGenerator),
      _currentWaveIndex(0),
      _waveTimer(0.0f),
      _isInDelayPeriod(false),
      _delayTimer(_interWaveDelay)
{
    initializeWaves();
}

void WaveManager::initializeWaves()
{
    Wave wave1(1, 20.0f);
    for (int i = 0; i < 4; ++i) {
        wave1.enemies.push_back(rtype::EnemyType::NORMAL);
    }
    for (int i = 0; i < 2; ++i) {
        wave1.enemies.push_back(rtype::EnemyType::FAST);
    }
    _waves.push_back(wave1);

    Wave wave2(2, 45.0f);
    for (int i = 0; i < 8; ++i) {
        wave2.enemies.push_back(rtype::EnemyType::NORMAL);
    }
    for (int i = 0; i < 4; ++i) {
        wave2.enemies.push_back(rtype::EnemyType::FAST);
    }
    _waves.push_back(wave2);

    Wave wave3(3, 60.0f);
    for (int i = 0; i < 16; ++i) {
        wave3.enemies.push_back(rtype::EnemyType::NORMAL);
    }
    for (int i = 0; i < 4; ++i) {
        wave3.enemies.push_back(rtype::EnemyType::FAST);
    }
    wave3.enemies.push_back(rtype::EnemyType::BOSS);
    _waves.push_back(wave3);

    _currentWaveIndex = 0;
    _waveTimer = 0.0f;
}

void WaveManager::updateWaves(float deltaTime)
{
    if (_currentWaveIndex < _waves.size()) {
        std::cout << "Wave " << _currentWaveIndex << std::endl;
        std::cout << "Wave active: " << _waves[_currentWaveIndex].isActive << std::endl;

        if (_isInDelayPeriod) {
            handleInterWaveDelay(deltaTime);
        } else {
            updateCurrentWave(deltaTime);
        }
    }
}

void WaveManager::handleInterWaveDelay(float deltaTime)
{
    _delayTimer -= deltaTime;

    if (_delayTimer <= 0) {
        _delayTimer = _interWaveDelay;
        _isInDelayPeriod = false;
        _currentWaveIndex++;
    }
}

void WaveManager::updateCurrentWave(float deltaTime)
{
    Wave& currentWave = _waves[_currentWaveIndex];

    if (!currentWave.isActive) {
        startWave(currentWave);
    } else {
        _waveTimer += deltaTime;
        std::cout << "Wave " << currentWave.number << " timer: " << _waveTimer << std::endl;

        if (_waveTimer >= currentWave.duration) {
            std::cout << "Wave " << currentWave.number << " timer: " << _waveTimer << std::endl;

            endWave(currentWave);
            _waveTimer = 0.0f;
            _isInDelayPeriod = true;
        }
    }
}

void WaveManager::startWave(Wave& wave)
{
    if (!wave.isActive) {
        wave.isActive = true;

        for (const auto& enemyType : wave.enemies) {
            spawnEnemy(enemyType);
        }
    }
}

void WaveManager::spawnEnemy(rtype::EnemyType enemyType)
{
    std::uint32_t newEnemyId = _idGenerator.generateId();
    std::cout << "New enemy id: " << newEnemyId << std::endl;
    entt::entity playerEntityId = static_cast<entt::entity>(newEnemyId);

    switch (enemyType) {
        case rtype::EnemyType::NORMAL: {
            float randomNormalX = WINDOW_WIDTH + 100;
            float randomNormalY = getRandomFloat(0.0f, WINDOW_HEIGHT - 64.0f);
            float randomNormalSpeed = getRandomFloat(2.0f, 5.0f);
            _entityManager.createNormalEnemy(
                playerEntityId, std::make_pair(randomNormalX, randomNormalY), randomNormalSpeed
            );
            break;
        }
        case rtype::EnemyType::FAST: {
            float randomNormalX = getRandomFloat(32.0f, WINDOW_WIDTH - 32.0f);
            float randomNormalY = -100;
            _entityManager.createFastEnemy(
                playerEntityId, std::make_pair(randomNormalX, randomNormalY), 10.0f
            );
            break;
        }
        case rtype::EnemyType::BOSS:
            // TODO : Implement boss enemy
            break;
        default:
            break;
    }
}

void WaveManager::endWave(Wave& wave)
{
    _isInDelayPeriod = true;
    _delayTimer = _interWaveDelay;
    wave.isActive = false;

    auto view = _entityManager.getRegistry().view<EnemyComponent>();

    for (auto entity : view) {
        _entityManager.getRegistry().destroy(entity);
    }
}

Wave& WaveManager::getCurrentWave()
{
    return _waves[_currentWaveIndex];
}

int WaveManager::getCurrentWaveIndex()
{
    return _currentWaveIndex;
}

float WaveManager::getWaveTimer()
{
    return _waveTimer;
}

float WaveManager::getDelayTimer()
{
    return _delayTimer;
}

bool WaveManager::getIsInDelayPeriod()
{
    return _isInDelayPeriod;
}
