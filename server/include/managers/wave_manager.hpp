#if !defined(WAVE_MANAGER_HPP)
#    define WAVE_MANAGER_HPP

#    include <vector>
#    include "../../../build/common/proto/r_type.pb.h"
#    include "../../../common/utils/id_generator.hpp"
#    include "./entity_manager.hpp"

struct Wave {
    int number;
    std::vector<rtype::EnemyType> enemies;
    bool isActive;
    float duration;

    Wave(int num, float dur) : number(num), isActive(false), duration(dur) {}
};

class WaveManager {
private:
    std::vector<Wave> _waves;
    int _currentWaveIndex;
    float _waveTimer;
    EntityManager& _entityManager;
    IdGenerator& _idGenerator;

    bool _isInDelayPeriod;
    float _delayTimer;
    const float _interWaveDelay = 5.0f;

    float getRandomFloat(float min, float max);

public:
    WaveManager(EntityManager& entityManager, IdGenerator& idGenerator);

    void initializeWaves();

    void updateWaves(float deltaTime);

    void handleInterWaveDelay(float deltaTime);

    void updateCurrentWave(float deltaTime);

    void startWave(Wave& wave);

    void spawnEnemy(rtype::EnemyType enemyType);

    void endWave(Wave& wave);
};

#endif  // WAVE_MANAGER_HPP
