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
            case GameScenes::About:
                std::cout << "About" << std::endl;
                break;
            default:
                std::cout << "Unknown" << std::endl;
                break;
        }
    }
};

#endif  // SCENE_MANAGER_HPP
