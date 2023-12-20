
#ifndef ECS_TRANSFORM_COMPONENT_HPP
#define ECS_TRANSFORM_COMPONENT_HPP

/*!
  @brief Transform component

  This component is used to store the position, rotation and scale of an entity
  in 2D space. It also stores the orientation of the entity in space, which is
  useful for side-scrolling games.

*/
struct TransformComponent {
  float x, y;
  float rotation;
  float scaleX, scaleY;
  float orientation;
};

#endif // ECS_TRANSFORM_COMPONENT_HPP
