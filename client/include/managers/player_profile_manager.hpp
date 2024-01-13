#if !defined(PLAYER_PROFILE_MANAGER_HPP)
#    define PLAYER_PROFILE_MANAGER_HPP

#    include <string>
#    include "../../../libs/EnTT/entt.hpp"

using std::string;

/**
 * @file player_profile_manager.hpp
 * @brief Defines the PlayerProfileManager class.
 */

/**
 * @class PlayerProfileManager
 * @brief This class is responsible for managing the player's profile.
 *
 * It uses the EnTT library to manage the player entity.
 */
class PlayerProfileManager {
private:
    string player_name;
    entt::entity playerEntity;

public:
    /**
     * @brief Constructs a new PlayerProfileManager.
     */
    PlayerProfileManager() = default;

    /**
     * @brief Sets the player entity.
     *
     * @param entity The new player entity.
     */
    void setPlayerEntity(entt::entity entity);

    /**
     * @brief Returns the player entity.
     *
     * @return The player entity.
     */
    entt::entity getPlayerEntity() const;

    /**
     * @brief Returns the name of the player.
     *
     * @return The name of the player.
     */
    [[nodiscard]] string getPlayerName() const;

    /**
     * @brief Sets the name of the player.
     *
     * @param name The new name of the player.
     */
    void setPlayerName(string name);
};

#endif  // PLAYER_PROFILE_MANAGER_HPP
