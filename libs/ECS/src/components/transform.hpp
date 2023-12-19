
#ifndef ECS_TRANSFORM_COMPONENT_HPP
#define ECS_TRANSFORM_COMPONENT_HPP

/*!
  @brief Transform component

  This component is used to store the position, rotation and scale of an entity
  in 2D space. It also stores the orientation of the entity in space, which is
  useful for side-scrolling games.

*/
struct TransformComponent {
  float x, y;           // Position in 2D space
  float rotation;       // Rotation in degrees
  float scaleX, scaleY; // Scale in X and Y
  float orientation;    // Orientation in space, useful for side-scrolling
};

#endif // ECS_TRANSFORM_COMPONENT_HPP
