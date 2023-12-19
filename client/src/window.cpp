#include "../include/game.hpp"

void game::windowLoop(ClientUDP &client) {
    Clock displayClock;
    Clock ticClock;
    Time displayElapsedTime;
    Time ticElapsedTime;
    Event event;
    Menu menu(_textures, _window);
    while(_window.isOpen()) {
        checkEvents(event);
        displayElapsedTime = displayClock.getElapsedTime();
        ticElapsedTime = ticClock.getElapsedTime();

        GameState state = _menu.getCurrentState();

        if (state == GameState::MAIN_MENU) {
            if (ticElapsedTime.asSeconds() >= 0.005f) {
                ticUpdates();
                ticClock.restart();
            }
            if (displayElapsedTime.asSeconds() >= 0.016f) {
                _window.clear();
                _window.draw(getParallax());
                _menu.draw(_window);
                _window.display();
                displayClock.restart();
            }
        } else if (state == GameState::GAME_RUNNING) {
            if (ticElapsedTime.asSeconds() >= 0.005f) {
                ticUpdates();
                ticClock.restart();
            }
            if (displayElapsedTime.asSeconds() >= 0.016f) {
                _window.clear();
                displayUpdates();
                _window.display();
                displayClock.restart();
            }
        }

        auto payload = client.get_payload();
    }
}

void game::displayUpdates() {
    _window.draw(getParallax());
    _window.draw(getPlanet());
    makeInfiniteAnimation(getPlanet(), _planetClock, 0, 0, 64, 64, 15.0f, 255);
    for (player &player : _players) {
        _window.draw(player.getSprite());
        makePlayerAnimation(player);
    }
}

void game::closeWindow(Event &event) {
    if (event.type == Event::Closed) {
        _window.close();
    }
}