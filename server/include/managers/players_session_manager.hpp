#if !defined(PLAYER_SESSION_MANAGER_HPP)
#    define PLAYER_SESSION_MANAGER_HPP

#    include <boost/array.hpp>
#    include <boost/asio.hpp>
#    include "../../../libs/EnTT/entt.hpp"
#    include "../utils.hpp"

using boost::asio::ip::udp;

/**
 * @class PlayerSession
 * @brief A class to manage a player's session in a networked game or application.
 */
class PlayerSession {
private:
    udp::endpoint endpoint_;
    entt::entity _playerEntity;

public:
    /**
     * @brief Construct a new Player Session object.
     *
     * @param endpoint The endpoint representing the IP address and port number of the player's session.
     * @param playerEntity The entity representing the player in the game.
     */
    PlayerSession(udp::endpoint endpoint, entt::entity playerEntity)
        : endpoint_(endpoint), _playerEntity(playerEntity)
    {
        std::cout << MAGENTA << "PlayerSession created for endpoint: " << endpoint_
                  << " with Player entity: " << static_cast<uint32_t>(_playerEntity) << RESET
                  << std::endl;
    }

    /**
     * @brief Get the endpoint object.
     *
     * @return udp::endpoint The endpoint representing the IP address and port number of the player's session.
     */
    udp::endpoint endpoint() const;

    /**
     * @brief Get the Player Entity object.
     *
     * @return entt::entity The entity representing the player in the game.
     */
    entt::entity getPlayerEntity() const;
};

#endif  // PLAYER_SESSION_MANAGER_HPP