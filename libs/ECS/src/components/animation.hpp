#include <map>
#include <string>

#ifndef ECS_ANIMATION_COMPONENT_HPP
#define ECS_ANIMATION_COMPONENT_HPP

struct AnimationComponent {
  std::string currentAnimation;
  // std::map<std::string, AnimationData> animations;
  float frameTime;
  float currentFrame;
};

#endif // ECS_ANIMATION_COMPONENT_HPP
