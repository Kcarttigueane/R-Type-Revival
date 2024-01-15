#if !defined(INPUT_MANAGER_HPP)
#    define INPUT_MANAGER_HPP

// Managers
#    include "../config.hpp"

// Libraries
#    include <queue>

#    include <SFML/Audio.hpp>
#    include <SFML/Graphics.hpp>
#    include <SFML/System.hpp>
#    include <SFML/Window.hpp>

#    include "../../../libs/EnTT/entt.hpp"

// #    include <format>
#    include <functional>
#    include <iostream>
#    include <map>
#    include <set>
#    include <sstream>

#    include <queue>

#    include "../../../build/common/proto/r_type.pb.h"
#    include "../../../common/components/component_includes.hpp"

/**
 * @file input_manager.hpp
 * @brief Defines the InputManager class.
 */

/**
 * @struct Actions
 * @brief Represents the actions that can be performed by the player.
 */
struct Actions {
    bool Shoot;
    bool Up = false;
    bool Down = false;
    bool Right;
    bool Left;
    bool Enter = false;
    bool Escape;
    bool Backspace;
    std::string TextInput;
};

/**
 * @class InputManager
 * @brief This class is responsible for managing the input in the game.
 *
 * It uses the SFML library to process keyboard events.
 */
class InputManager {
private:
    GameScenes _currentScene;
    entt::registry& _registry;
    sf::RenderWindow& _window;
    Actions keyboardActions;
    std::string currentTextInput;

public:
    /**
     * @brief Constructs a new InputManager.
     *
     * @param _registry The registry from EnTT.
     * @param window The SFML window.
     */
    InputManager(entt::registry& _registry, sf::RenderWindow& window);

    /**
     * @brief Returns the current game scene.
     *
     * @return The current game scene.
     */
    [[nodiscard]] GameScenes getContext() const;

    /**
     * @brief Sets the current game scene.
     *
     * @param context The new game scene.
     */
    void setContext(GameScenes context);

    /**
     * @brief Returns the actions that can be performed by the player.
     *
     * @return The actions that can be performed by the player.
     */
    [[nodiscard]] Actions& getKeyboardActions();

    /**
     * @brief Processes a key press event.
     *
     * @param event The SFML event.
     */
    void processKeyPress(sf::Event& event);

    /**
     * @brief Processes a key release event.
     *
     * @param event The SFML event.
     */
    void processKeyRelease(sf::Event& event);

    void processTextInput(sf::Event& event);

    void clearTextInput();
};

#endif  // INPUT_MANAGER_HPP
