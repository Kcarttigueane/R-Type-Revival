#ifndef TEXTURES_HPP_
#define TEXTURES_HPP_

#include "includes.hpp"

class textures {
protected:
    Texture _parallax;
    Texture _ships;
    Texture _planet;
    Texture _play;
    Texture _settings;
    Texture _exit;
    Texture _tutorial;
    Texture _about;
public:
    textures();
    Texture &getParallaxTexture();
    Texture &getShipsTexture();
    Texture &getPlanetTexture();
    Texture &getPlayTexture();
    Texture &getSettingsTexture();
    Texture &getExitTexture();
    Texture &getTutorialTexture();
    Texture &getAboutTexture();
    ~textures();
};

#endif /* !TEXTURES_HPP_ */
