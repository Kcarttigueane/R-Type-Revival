#include "../include/game.hpp"

string game::makeAnimation(player& player, int left, int top, int width,
                           int height, float time, int totalFrames,
                           string animation)
{
    float frameTime = time / totalFrames;
    float elapsedTime = player.getAnimationClock().getElapsedTime().asSeconds();
    int currentFrame =
        static_cast<int>((elapsedTime / frameTime)) % totalFrames;
    player.getSprite().setTextureRect(
        IntRect(left + currentFrame * width, top, width, height));
    if (currentFrame == totalFrames - 1 || currentFrame == totalFrames + 1) {
        player.getAnimationClock().restart();
        return "hold";
    } else {
        return animation;
    }
}

void game::makeInfiniteAnimation(Sprite& sprite, Clock& clock, int left,
                                 int top, int width, int height, float time,
                                 int totalFrames)
{
    float frameTime = time / totalFrames;
    float elapsedTime = clock.getElapsedTime().asSeconds();
    int currentFrame =
        static_cast<int>((elapsedTime / frameTime)) % totalFrames;
    sprite.setTextureRect(
        IntRect(left + currentFrame * width, top, width, height));
    if (currentFrame == totalFrames) {
        clock.restart();
    }
}
