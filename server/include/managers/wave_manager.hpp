#if !defined(WAVE_MANAGER_HPP)
#    define WAVE_MANAGER_HPP

#    include <vector>
#    include "../../../build/common/proto/r_type.pb.h"
#    include "../../../common/utils/id_generator.hpp"
#    include "./entity_manager.hpp"

/**
 * @file wave_manager.hpp
 * @brief File containing the WaveManager class and Wave struct.
 */

/**
 * @struct Wave
 * @brief Represents a wave of enemies in the game.
 */
struct Wave {
    int number;                             ///< The number of the wave.
    std::vector<rtype::EnemyType> enemies;  ///< The types of enemies in the wave.
    bool isActive;                          ///< Whether the wave is currently active.
    float duration;                         ///< The duration of the wave.

    /**
     * @brief Constructs a new Wave object.
     * @param num The number of the wave.
     * @param dur The duration of the wave.
     */
    Wave(int num, float dur) : number(num), isActive(false), duration(dur) {}
};

/**
 * @class WaveManager
 * @brief Manages the waves of enemies in the game.
 */
class WaveManager {
private:
    std::vector<Wave> _waves;
    int _currentWaveIndex;
    float _waveTimer;  ///< The timer for the current wave.
    EntityManager& _entityManager;
    IdGenerator& _idGenerator;

    bool _isInDelayPeriod;  ///< Whether the game is currently in a delay period between waves.
    float _delayTimer;      ///< The timer for the delay period.
    const float _interWaveDelay = 5.0f;  ///< The duration of the delay period.

    /**
     * @brief Generates a random float between min and max.
     * @param min The minimum value.
     * @param max The maximum value.
     * @return A random float between min and max.
     */
    float getRandomFloat(float min, float max);

public:
    /**
     * @brief Constructs a new WaveManager object.
     * @param entityManager Reference to the EntityManager.
     * @param idGenerator Reference to the IdGenerator.
     */
    WaveManager(EntityManager& entityManager, IdGenerator& idGenerator);

    /**
     * @brief Initializes the waves.
     */
    void initializeWaves();

    /**
     * @brief Updates the waves based on the passed time.
     * @param deltaTime The time passed since the last update.
     */
    void updateWaves(float deltaTime);

    /**
     * @brief Handles the delay period between waves.
     * @param deltaTime The time passed since the last update.
     */
    void handleInterWaveDelay(float deltaTime);

    /**
     * @brief Updates the current wave based on the passed time.
     * @param deltaTime The time passed since the last update.
     */
    void updateCurrentWave(float deltaTime);

    /**
     * @brief Starts a wave.
     * @param wave The wave to start.
     */
    void startWave(Wave& wave);

    /**
     * @brief Spawns an enemy of the specified type.
     * @param enemyType The type of enemy to spawn.
     */
    void spawnEnemy(rtype::EnemyType enemyType);

    /**
     * @brief Ends a wave.
     * @param wave The wave to end.
     */
    void endWave(Wave& wave);

    /**
     * @brief Gets the current wave.
     * @return The current wave.
     */
    Wave& getCurrentWave();

    /**
     * @brief Gets the current wave index.
     * @return The current wave index.
     */
    int getCurrentWaveIndex();

    /**
     * @brief Gets the current wave timer.
     * @return The current wave timer.
     */
    float getWaveTimer();

    /**
     * @brief Gets the delay timer.
     * @return The delay timer.
     */
    float getDelayTimer();

    /**
     * @brief Gets whether the game is currently in a delay period between waves.
     * @return Whether the game is currently in a delay period between waves.
     */
    bool getIsInDelayPeriod();
};

#endif  // WAVE_MANAGER_HPP
