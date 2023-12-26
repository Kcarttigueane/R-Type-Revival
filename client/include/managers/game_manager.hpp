#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

// Managers
#include "./input_manager.hpp"
#include "./network_manager.hpp"
#include "./player_profile_manager.hpp"
#include "./resource_manager.hpp"
#include "./scene_manager.hpp"
#include "./settings_manager.hpp"

// Libraries
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <SFML/Window.hpp>
#include <iostream>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

class GameManager {
private:
    // Game
    sf::RenderWindow _window;

    // Managers
    InputManager _input_manager;
    NetworkManager _network_manager;
    PlayerProfileManager _player_profile_manager;
    ResourceManager _resource_manager;
    SceneManager _scene_manager;
    SettingsManager _settings_manager;

public:
    GameManager()
        : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Type-Revival"),
          _input_manager(),
          _network_manager(),
          _player_profile_manager(),
          _resource_manager(),
          _scene_manager(_input_manager),
          _settings_manager(_resource_manager)
    {
        std::cout << "GameManager created!" << std::endl;
    }

    ~GameManager() = default;

    void start_game() { std::cout << "Hello World!" << std::endl; }

    void game_loop()
    {
        while (_window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
                if (isInputEvent(event)) {
                    _input_manager.processInput(event);
                }
            }
            _window.display();
            _window.clear();
        }
    }

    bool isInputEvent(const sf::Event& event)
    {
        // TODO: Add more input events if needed define scope with gars
        return event.type == sf::Event::KeyPressed ||
               event.type == sf::Event::KeyReleased ||
               event.type == sf::Event::MouseButtonPressed ||
               event.type == sf::Event::MouseButtonReleased;
    }
};

#endif  // GAME_MANAGER_HPP
