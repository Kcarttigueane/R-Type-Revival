#include <string>
#include <map>

#ifndef ECS_ANIMATION_COMPONENT_HPP
#define ECS_ANIMATION_COMPONENT_HPP


struct AnimationComponent {
  std::string currentAnimation;
  // std::map<std::string, AnimationData> animations;     // Map of animation states and their data
  float frameTime;    // Time per frame
  float currentFrame; // Current frame in the animation
};

#endif // ECS_ANIMATION_COMPONENT_HPP
