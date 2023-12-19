#ifndef ECS_COMPONENTS_HEALTH_HPP
#define ECS_COMPONENTS_HEALTH_HPP

struct HealthComponent {
  int healthPoints;
  float invulnerabilityDuration; // Time in seconds of invulnerability after hit
  float invulnerabilityTimer;    // Current timer for invulnerability
};

#endif // ECS_COMPONENTS_HEALTH_HPP
