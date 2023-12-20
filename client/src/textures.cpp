#include "../include/game.hpp"

textures::textures(string assetsPath)
{
    _parallax.loadFromFile(assetsPath +
                           "/Background/Layer 3/Space_background.png");
    _ships.loadFromFile(assetsPath + "/Player/spaceship.gif");
    _planet.loadFromFile(assetsPath + "/Background/Layer 1/Wet.png");
}

Texture& textures::getParallaxTexture()
{
    return _parallax;
}

Texture& textures::getShipsTexture()
{
    return _ships;
}

Texture& textures::getPlanetTexture()
{
    return _planet;
}

textures::~textures() {}
