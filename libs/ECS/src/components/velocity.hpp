#ifndef ECS_VELOCITY_COMPONENT_HPP
#define ECS_VELOCITY_COMPONENT_HPP

struct VelocityComponent {
  float x, y;
  float acceleration;
  float deceleration;
};

#endif // ECS_VELOCITY_COMPONENT_HPP
