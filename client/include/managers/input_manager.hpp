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

#    include "../../../common/components/component_includes.hpp"
#    include "../../src/proto/r_type.pb.h"

struct Actions {
    bool Shoot;
    bool Up;
    bool Down;
    bool Right;
    bool Left;
};

class InputManager {
private:
    GameScenes _currentScene;
    entt::registry& _registry;
    sf::RenderWindow& _window;
    Actions keyboardActions;

public:
    InputManager() = delete;

    InputManager(entt::registry& _registry, sf::RenderWindow& window)
        : _currentScene(GameScenes::MainMenu), _registry(_registry), _window(window)
    {}

    ~InputManager() = default;

    [[nodiscard]] GameScenes getContext() const;

    void setContext(GameScenes context);

    [[nodiscard]] Actions& getKeyboardActions();

    void processKeyPress(sf::Event& event);

    void processKeyRelease(sf::Event& event);
};

#endif  // INPUT_MANAGER_HPP
