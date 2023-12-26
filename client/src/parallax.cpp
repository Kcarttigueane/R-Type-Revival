#include "../include/game.hpp"

void game::initParallax(textures& textures)
{
    _parallax.setTexture(textures.getParallaxTexture());
    _parallax.setPosition(Vector2f(0.0f, 0.0f));

    _planet.setTexture(textures.getPlanetTexture());
    _planet.setScale(Vector2f(2.0f, 2.0f));
    _planet.setPosition(Vector2f(220.0f, 220.0f));
}

Sprite& game::getParallax()
{
    return _parallax;
}

Sprite& game::getPlanet()
{
    return _planet;
}

void game::resetParallax()
{
    Sprite& parallax = getParallax();
    if (parallax.getPosition().x <= -1920.0f) {
        parallax.setPosition(Vector2f(0.0f, 0.0f));
    }
}

void game::moveParallax()
{
    Sprite& parallax = getParallax();
    parallax.setPosition(Vector2f(parallax.getPosition().x - 1.0f, 0.0f));
}
