#ifndef ECS_WEAPON_COMPONENT_HPP
#define ECS_WEAPON_COMPONENT_HPP

#include <string>
#include <vector>

enum class WeaponType {
    NORMAL,
    PLASMA,
    NONE,
};

struct WeaponComponent {
    WeaponType type;
    std::vector<std::string> upgradePaths;
    float fireRate;
    int currentAmmo;
    bool alternateFire;
};

struct PlayerProjectileComponent {};

struct EnemyProjectileComponent {};

#endif  // ECS_WEAPON_COMPONENT_HPP
