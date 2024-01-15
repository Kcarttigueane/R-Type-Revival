
#ifndef ECS_ENEMY_COMPONENT_HPP
#define ECS_ENEMY_COMPONENT_HPP

enum class EnemyType {
    NORMAL,
    FAST,
    BOSS,
};

struct EnemyComponent {
    EnemyType type;
};

#endif  // ECS_ENEMY_COMPONENT_HPP
