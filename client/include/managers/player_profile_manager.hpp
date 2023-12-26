#if !defined(PLAYER_PROFILE_MANAGER_HPP)
#    define PLAYER_PROFILE_MANAGER_HPP

#    include <string>

using std::string;

class PlayerProfileManager {
private:
    string player_name;
    string player_id;

public:
    PlayerProfileManager(/* args */) = default;
    ~PlayerProfileManager() = default;

    [[nodiscard]] string getPlayerName() const { return player_name; }

    void setPlayerName(string name) { player_name = name; }

    [[nodiscard]] string getPlayerId() const { return player_id; }

    void setPlayerId(string id) { player_id = id; }
};

#endif  // PLAYER_PROFILE_MANAGER_HPP
