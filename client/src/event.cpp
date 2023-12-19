#include "../include/game.hpp"

void game::checkEvents(Event &event) {
    while (_window.pollEvent(event)) {
        closeWindow(event);
        checkMovementKeyPress(event);
        checkMovementKeyRelease(event);
    }
}