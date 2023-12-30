// #include "../include/game.hpp"

// string game::makeAnimation(
//     player& player, sf::IntRect rect, float time, int totalFrames,
//     string animation
// )
// {
//     float frameTime = time / totalFrames;
//     float elapsedTime = player.getAnimationClock().getElapsedTime().asSeconds();
//     int currentFrame =
//         static_cast<int>((elapsedTime / frameTime)) % totalFrames;
//     player.getSprite().setTextureRect(IntRect(
//         rect.left + currentFrame * rect.width, rect.top, rect.width, rect.height
//     ));
//     if (currentFrame == totalFrames - 1 || currentFrame == totalFrames + 1) {
//         player.getAnimationClock().restart();
//         return "hold";
//     } else {
//         return animation;
//     }
// }

// void game::makeInfiniteAnimation(
//     Sprite& sprite, Clock& clock, sf::IntRect rect, float time, int totalFrames
// )
// {
//     float frameTime = time / totalFrames;
//     float elapsedTime = clock.getElapsedTime().asSeconds();
//     int currentFrame =
//         static_cast<int>((elapsedTime / frameTime)) % totalFrames;
//     sprite.setTextureRect(IntRect(
//         rect.left + currentFrame * rect.width, rect.top, rect.width, rect.height
//     ));
//     if (currentFrame == totalFrames) {
//         clock.restart();
//     }
// }
