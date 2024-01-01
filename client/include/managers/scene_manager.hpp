#if !defined(SCENE_MANAGER_HPP)
#    define SCENE_MANAGER_HPP

#    include "input_manager.hpp"

class SceneManager {
private:
    GameScenes _current_scene = GameScenes::InGame;
    InputManager& _inputManager;

public:
    SceneManager() = delete;

    SceneManager(InputManager& input_manager) : _inputManager(input_manager) {}

    ~SceneManager() = default;

    [[nodiscard]] GameScenes getCurrentScene() const { return _current_scene; }

    void setCurrentScene(GameScenes scene) { _current_scene = scene; }

    void getCurrentSceneName() const
    {
        switch (_current_scene) {
            case GameScenes::MainMenu:
                std::cout << "MainMenu" << std::endl;
                break;
            case GameScenes::InGame:
                std::cout << "InGame" << std::endl;
                break;
            case GameScenes::GameOver:
                std::cout << "GameOver" << std::endl;
                break;
            case GameScenes::Settings:
                std::cout << "Settings" << std::endl;
                break;
            case GameScenes::Tutorial:
                std::cout << "Credits" << std::endl;
                break;
            case GameScenes::Quit:
                std::cout << "Quit" << std::endl;
                break;
            case GameScenes::PauseMenu:
                std::cout << "PauseMenu" << std::endl;
                break;
            default:
                std::cout << "Unknown" << std::endl;
                break;
        }
    }
};

#endif  // SCENE_MANAGER_HPP
