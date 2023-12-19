#include "../include/game.hpp"

void game::checkEvents(Event &event) {
    while (_window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            _window.close();
        }

        GameState state = _menu.getCurrentState();

        if (state == GameState::MAIN_MENU) {
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Right) {
                    _menu.moveMenu(-1);
                } else if (event.key.code == Keyboard::Left) {
                    _menu.moveMenu(1);
                }
            }
        } else if (state == GameState::GAME_RUNNING) {
            checkMovementKeyPress(event);
            checkMovementKeyRelease(event);
        }
    }
}