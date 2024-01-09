#if !defined(SCENE_COMPONENT_HPP)
#    define SCENE_COMPONENT_HPP

#    include <optional>

enum class GameScenes {
    InGame,
    MainMenu,
    Settings,
    PauseMenu,
    GameOver,
    Tutorial,
    Quit,
    Lose,
    Win,
};

struct SceneComponent {
    std::optional<GameScenes> scene;

    // SceneComponent() : scene(std::nullopt) {}  // For entities in all sc
    SceneComponent() = default;

    explicit SceneComponent(GameScenes scene) : scene(scene) {}
};

#endif  // SCENE_COMPONENT_HPP
