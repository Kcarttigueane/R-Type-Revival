#include "../include/game.hpp"

player::player(int id, string type, Texture& shipsTexture)
{
    _id = id;
    _type = type;
    _sprite.setTexture(shipsTexture);
    _sprite.setTextureRect(IntRect(66, 0, 33, 17));
    _sprite.setScale(Vector2f(5.0, 5.0));
}

void player::setPosition(float x, float y)
{
    _position = Vector2f(x, y);
}

Vector2f player::getPosition()
{
    return _position;
}

Sprite& player::getSprite()
{
    return _sprite;
}

string player::getType()
{
    return _type;
}

void player::move(float x, float y)
{
    _position = Vector2f(_position.x + x, _position.y + y);
    _sprite.setPosition(_position);
}

string player::getAnimation()
{
    return _animation;
}

void player::setAnimation(string status)
{
    _animation = status;
}

Clock& player::getAnimationClock()
{
    return _animationClock;
}

void game::moveLocalPlayer()
{
    player& localPlayer = getLocalPlayer();
    if (_move_left == 1) {
        localPlayer.move(-2.0, 0.0);
        std::lock_guard<std::mutex> lock(_messages_mutex);
        _messages.push(std::to_string(Keyboard::Left));
    }
    if (_move_right == 1) {
        localPlayer.move(2.0, 0.0);
        std::lock_guard<std::mutex> lock(_messages_mutex);
        _messages.push(std::to_string(Keyboard::Right));
    }
    if (_move_up == 1) {
        localPlayer.move(0.0, -2.0);
        std::lock_guard<std::mutex> lock(_messages_mutex);
        _messages.push(std::to_string(Keyboard::Up));
    }
    if (_move_down == 1) {
        localPlayer.move(0.0, 2.0);
        std::lock_guard<std::mutex> lock(_messages_mutex);
        _messages.push(std::to_string(Keyboard::Down));
    }
}

void game::checkMovementKeyPress(Event& event)
{
    for (player& player : _players) {
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Left) {
                _move_left = 1;
            }
            if (event.key.code == Keyboard::Right) {
                _move_right = 1;
            }
            if (event.key.code == Keyboard::Up) {
                _move_up = 1;
                if (player.getAnimation() != "hold")
                    player.setAnimation("up");
            }
            if (event.key.code == Keyboard::Down) {
                _move_down = 1;
                if (player.getAnimation() != "hold")
                    player.setAnimation("down");
            }
            if (event.key.code == Keyboard::Space) {
                _sound.play();
            }
        }
    }
}

void game::checkMovementKeyRelease(Event& event)
{
    for (player& player : _players) {
        if (event.type == Event::KeyReleased) {
            if (event.key.code == Keyboard::Left) {
                _move_left = 0;
            }
            if (event.key.code == Keyboard::Right) {
                _move_right = 0;
            }
            if (event.key.code == Keyboard::Up) {
                _move_up = 0;
                player.setAnimation("static");
            }
            if (event.key.code == Keyboard::Down) {
                _move_down = 0;
                player.setAnimation("static");
            }
        }
    }
}

player& game::getLocalPlayer()
{
    for (player& player : _players) {
        if (player.getType() == "local") {
            return player;
        }
    }
    exit(84);
}

player::~player() {}
