#if !defined(CONFIG_HPP)
#    define CONFIG_HPP

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

enum class GameScenes {
    InGame,
    Lobby,
    MainMenu,
    Settings,
    PauseMenu,
    GameOver,
    Tutorial,
    About,
    Quit,
    Lose,
    Win,
};

#endif  // CONFIG_HPP
