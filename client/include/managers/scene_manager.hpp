#if !defined(SCENE_MANAGER_HPP)
#    define SCENE_MANAGER_HPP

#    include "input_manager.hpp"

class SceneManager {
private:
    GameScenes _current_scene = GameScenes::MainMenu;
    InputManager& _input_manager;

public:
    SceneManager() = delete;

    SceneManager(InputManager& input_manager) : _input_manager(input_manager) {}

    ~SceneManager() = default;
};

#endif  // SCENE_MANAGER_HPP
