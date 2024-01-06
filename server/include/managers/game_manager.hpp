#if !defined(GAME_MANGER_HPP)
#    define GAME_MANGER_HPP

#    include "./entity_manager.hpp"
#    include "./network_manager.hpp"
#    include "./players_session_manager.hpp"

struct GameMetadata {
    int currentLevel;
    int highestScore;

    GameMetadata() : currentLevel(1), highestScore(0) {}

    void reset()
    {
        currentLevel = 1;
        highestScore = 0;
    }

    void updateLevel(int level) { currentLevel = level; }

    void updateScore(int score)
    {
        if (score > highestScore) {
            highestScore = score;
        }
    }
};

class GameManager {
private:
    entt::registry _registry;
    boost::asio::io_context _io_context;

    // ! Game metadata
    GameMetadata _game_metadata;

    // ! Managers
    EntityManager _entity_manager;
    NetworkManager _network_manager;
    // PlayerSessionManagerUDP _players_manager;

public:
    GameManager(const std::string& server_address, unsigned short port)
        : _entity_manager(_registry), _network_manager(_io_context, port)
    {}

    ~GameManager() = default;

    void run()
    {
        std::thread send_payload_thread([&]() { _network_manager.send_payload_thread(); });
        _io_context.run();
    }
};

#endif  // GAME_MANGER_HPP
