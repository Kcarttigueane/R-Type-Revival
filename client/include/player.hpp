#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "includes.hpp"

class player {
protected:
    int _id;
    string _animation = "static";
    Sprite _sprite;
    string _type;
    Vector2f _position;
    Clock _animationClock;
public:
    player(int id, string type, Texture &shipsTextures);
    void setPosition(float x, float y);
    Vector2f getPosition();
    Sprite &getSprite();
    string getType();
    void move(float x, float y);
    string getAnimation();
    void setAnimation(string status);
    Clock &getAnimationClock();
    ~player();
};

#endif /* !PLAYER_HPP_ */
