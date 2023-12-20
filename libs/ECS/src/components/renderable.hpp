
#ifndef ECS_RENDERABLE_COMPONENT_HPP
#define ECS_RENDERABLE_COMPONENT_HPP

#include "../../include/ecs.hpp"

struct RenderableComponent {
  std::string spriteID; // Reference to a sprite or image asset
  int layer;            // Render layer for depth effect
  int zIndex;           // Z-index for sorting objects within the same layer
};

#endif // ECS_RENDERABLE_COMPONENT_HPP
