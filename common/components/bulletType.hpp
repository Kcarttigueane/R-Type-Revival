#ifndef ECS_BULLET_COMPONENT_HPP
#define ECS_BULLET_COMPONENT_HPP

enum class EntityType {
    PLAYER,
    ENEMY
};

struct BulletTypeComponent {
    EntityType type;
};

#endif  // ECS_BULLET_COMPONENT_HPP