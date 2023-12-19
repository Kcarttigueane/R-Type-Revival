#ifndef ECS_VELOCITY_COMPONENT_HPP
#define ECS_VELOCITY_COMPONENT_HPP

struct VelocityComponent {
  float x, y;         // Velocity in X and Y
  float acceleration; // Acceleration rate
  float deceleration; // Deceleration rate
};

#endif // ECS_VELOCITY_COMPONENT_HPP
