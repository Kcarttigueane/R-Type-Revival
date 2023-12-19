#ifndef TEXTURES_HPP_
#define TEXTURES_HPP_

#include "includes.hpp"

class textures {
protected:
    Texture _parallax;
    Texture _ships;
    Texture _planet;
public:
    textures(string assetsPath);
    Texture &getParallaxTexture();
    Texture &getShipsTexture();
    Texture &getPlanetTexture();
    ~textures();
};

#endif /* !TEXTURES_HPP_ */
