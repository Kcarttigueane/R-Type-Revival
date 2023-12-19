
#ifndef ECS_COLLIDER_COMPONENT_HPP
#define ECS_COLLIDER_COMPONENT_HPP

#include <vector>

struct ColliderComponent {
  enum class ColliderType { BOX, CIRCLE, POLYGON } type;
  std::vector<float> data; // Coordinates for collider shape
  // Collision response data can include callback functions or references to
  // handling systems
};

#endif // ECS_COLLIDER_COMPONENT_HPP
