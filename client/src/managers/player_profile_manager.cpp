#include "../../include/managers/player_profile_manager.hpp"

void PlayerProfileManager::setPlayerEntity(entt::entity entity)
{
    playerEntity = entity;
}

entt::entity PlayerProfileManager::getPlayerEntity() const
{
    return playerEntity;
}

[[nodiscard]] string PlayerProfileManager::getPlayerName() const
{
    return player_name;
}

void PlayerProfileManager::setPlayerName(string name)
{
    player_name = name;
}

[[nodiscard]] float PlayerProfileManager::getPlayerHealth() const
{
    return player_health;
}

void PlayerProfileManager::setPlayerHealth(float health)
{
    player_health = health;
}