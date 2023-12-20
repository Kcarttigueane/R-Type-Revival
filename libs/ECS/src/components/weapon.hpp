#ifndef ECS_WEAPON_COMPONENT_HPP
#define ECS_WEAPON_COMPONENT_HPP

#include <string>
#include <vector>

struct WeaponComponent {
  std::string weaponType;
  std::vector<std::string> upgradePaths;
  float fireRate;
  int currentAmmo;
  bool alternateFire;
};

#endif // ECS_WEAPON_COMPONENT_HPP
