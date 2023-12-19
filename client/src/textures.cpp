#include "../include/game.hpp"

textures::textures() {
    _parallax.loadFromFile("../../client/assets/background/layer_3/space_background.png");
    _ships.loadFromFile("../../client/assets/player/spaceship.gif");
    _planet.loadFromFile("../../client/assets/background/layer_1/wet.png");
    _play.loadFromFile("../../client/assets/menu/play.png");
    _settings.loadFromFile("../../client/assets/menu/settings.png");
    _exit.loadFromFile("../../client/assets/menu/exit.png");
    _tutorial.loadFromFile("../../client/assets/menu/tutorial.png");
    _about.loadFromFile("../../client/assets/menu/about.png");
}

Texture &textures::getPlayTexture() {
    return _play;
}

Texture &textures::getSettingsTexture() {
    return _settings;
}

Texture &textures::getExitTexture() {
    return _exit;
}

Texture &textures::getTutorialTexture() {
    return _tutorial;
}

Texture &textures::getAboutTexture() {
    return _about;
}

Texture &textures::getParallaxTexture() {
    return _parallax;
}

Texture &textures::getShipsTexture() {
    return _ships;
}

Texture &textures::getPlanetTexture() {
    return _planet;
}

textures::~textures() {}