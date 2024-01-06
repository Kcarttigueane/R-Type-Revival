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

    void setPlayerEntity(entt::entity entity);

    entt::entity getPlayerEntity() const;

    [[nodiscard]] string getPlayerName() const;

    void setPlayerName(string name);
};

#endif  // PLAYER_PROFILE_MANAGER_HPP
