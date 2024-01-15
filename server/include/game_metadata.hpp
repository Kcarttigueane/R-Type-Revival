#if !defined(GAME_METADATA_HPP)
#    define GAME_METADATA_HPP

struct GameMetadata {
    bool isRunning = true;
    int currentLevel;
    int highestScore;

    GameMetadata() : currentLevel(1), highestScore(0) {}

    void reset()
    {
        currentLevel = 1;
        highestScore = 0;
    }

    void updateLevel(int level) { currentLevel = level; }

    void updateScore(int score)
    {
        if (score > highestScore) {
            highestScore = score;
        }
    }
};

#endif  // GAME_METADATA_HPP
