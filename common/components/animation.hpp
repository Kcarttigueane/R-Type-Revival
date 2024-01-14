#ifndef ECS_ANIMATION_COMPONENT_HPP
#define ECS_ANIMATION_COMPONENT_HPP

#include "SFML/System.hpp"

struct HoldAnimationComponent {
    int totalFrames;
    float animationTime;
    bool status;
    sf::Clock animationClock;

    HoldAnimationComponent(int frames, float time, bool s)
        : totalFrames(frames), animationTime(time), status(s)
    {}
};

struct SingleAnimationComponent {
    int totalFrames;
    float animationTime;
    sf::Clock animationClock;

    SingleAnimationComponent(int frames, float time) : totalFrames(frames), animationTime(time) {}
};

struct InfiniteAnimationComponent {
    int totalFrames;
    float animationTime;
    sf::Clock animationClock;

    InfiniteAnimationComponent(int frames, float time) : totalFrames(frames), animationTime(time) {}
};

#endif  // ECS_ANIMATION_COMPONENT_HPP
