#ifndef ECS_WEAPON_COMPONENT_HPP
#define ECS_WEAPON_COMPONENT_HPP

#include <string>
#include <vector>

struct WeaponComponent {
  std::string weaponType;
  std::vector<std::string> upgradePaths; // List of possible upgrades
  float fireRate;                        // Bullets per second
  int currentAmmo;                       // Current ammo count
  bool alternateFire;                    // Toggle for alternate firing mode
};

#endif // ECS_WEAPON_COMPONENT_HPP
