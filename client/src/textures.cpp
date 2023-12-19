#include "../include/game.hpp"

textures::textures() {
    _parallax.loadFromFile("../../client/assets/Background/Layer 3/Space_background.png");
    _ships.loadFromFile("../../client/assets/Player/spaceship.gif");
    _planet.loadFromFile("../../client/assets/Background/Layer 1/Wet.png");
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