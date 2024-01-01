#if !defined(PLAYER_PROFILE_MANAGER_HPP)
#    define PLAYER_PROFILE_MANAGER_HPP

#    include <string>
#    include "../../../libs/EnTT/entt.hpp"

using std::string;

class PlayerProfileManager {
private:
    string player_name;
    entt::entity playerEntity;

public:
    PlayerProfileManager() = default;
    ~PlayerProfileManager() = default;

    void setPlayerEntity(entt::entity entity) { playerEntity = entity; }

    entt::entity getPlayerEntity() const { return playerEntity; }

    [[nodiscard]] string getPlayerName() const { return player_name; }

    void setPlayerName(string name) { player_name = name; }
};

#endif  // PLAYER_PROFILE_MANAGER_HPP
