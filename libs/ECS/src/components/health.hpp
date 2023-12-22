#ifndef ECS_COMPONENTS_HEALTH_HPP
#define ECS_COMPONENTS_HEALTH_HPP

struct HealthComponent {
  int healthPoints;
  float invulnerabilityDuration;
  float invulnerabilityTimer;

  HealthComponent(float health, float maxHealth, float anotherParameter)
      : healthPoints(health), invulnerabilityDuration(maxHealth),
        invulnerabilityTimer(anotherParameter) {}

  int getHealth() { return healthPoints; }
};

#endif // ECS_COMPONENTS_HEALTH_HPP
