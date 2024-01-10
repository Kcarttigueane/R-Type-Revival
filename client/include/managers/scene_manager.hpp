#if !defined(SCENE_MANAGER_HPP)
#    define SCENE_MANAGER_HPP

#    include "input_manager.hpp"

/**
 * \class SceneManager
 * \brief Manages different scenes in the game.
 *
 * This class is responsible for managing the transitions between
 * different scenes in the game. It interacts with the InputManager
 * to manage scene changes.
 */
class SceneManager {
private:
    GameScenes _current_scene = GameScenes::MainMenu;
    InputManager& _inputManager;

public:
    SceneManager() = delete;

    SceneManager(InputManager& input_manager) : _inputManager(input_manager) {}

    ~SceneManager() = default;

    [[nodiscard]] GameScenes getCurrentScene() const;

    void setCurrentScene(GameScenes scene);

    void getCurrentSceneName() const;
};

#endif  // SCENE_MANAGER_HPP
