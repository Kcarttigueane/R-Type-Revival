#include "../include/game.hpp"

textures::textures() {
    _parallax.loadFromFile("../../client/assets/background/layer_3/space_background.png");
    _ships.loadFromFile("../../client/assets/player/spaceship.gif");
    _planet.loadFromFile("../../client/assets/background/layer_1/wet.png");
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