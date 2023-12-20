
#ifndef ECS_COLLIDER_COMPONENT_HPP
#define ECS_COLLIDER_COMPONENT_HPP

#include <vector>

struct ColliderComponent {
  enum class ColliderType { BOX, CIRCLE, POLYGON } type;
  std::vector<float> data;
};

#endif // ECS_COLLIDER_COMPONENT_HPP
