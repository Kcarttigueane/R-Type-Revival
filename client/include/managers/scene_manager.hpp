#if !defined(SCENE_MANAGER_HPP)
#    define SCENE_MANAGER_HPP

#    include "input_manager.hpp"

/**
 * @file scene_manager.hpp
 * @brief File containing the SceneManager class.
 */

/**
 * @class SceneManager
 * @brief Manages different scenes in the game.
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
    /**
     * @brief Deleted default constructor.
     */
    SceneManager() = delete;

    /**
     * @brief Constructs a new SceneManager object.
     * @param input_manager Reference to the InputManager.
     */
    SceneManager(InputManager& input_manager);

    /**
     * @brief Default destructor.
     */
    ~SceneManager() = default;

    /**
     * @brief Gets the current scene.
     * @return The current scene.
     */
    [[nodiscard]] GameScenes getCurrentScene() const;

    /**
     * @brief Sets the current scene.
     * @param scene The scene to set as the current scene.
     */
    void setCurrentScene(GameScenes scene);
};

#endif  // SCENE_MANAGER_HPP
