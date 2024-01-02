#if !defined(GAME_MANGER_HPP)
#    define GAME_MANGER_HPP

#    include "./entity_manager.hpp"
#    include "./network_manager.hpp"
#    include "./players_manager.hpp"

class GameManager {
private:
    EntityManager _entity_manager;
    NetworkManager _network_manager;
    PlayersManager _players_manager;

public:
    GameManager(const std::string& server_address, unsigned short port)
        : _network_manager(port)
    {}

    ~GameManager() = default;

    void run() {}
};

#endif  // GAME_MANGER_HPP
