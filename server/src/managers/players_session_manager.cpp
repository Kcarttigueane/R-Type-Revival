#include "../../include/managers/players_session_manager.hpp"

PlayerSession::PlayerSession(udp::endpoint endpoint, entt::entity playerEntity)
    : endpoint_(endpoint), _playerEntity(playerEntity)
{
    std::cout << MAGENTA << "PlayerSession created for endpoint: " << endpoint_
              << " with Player entity: " << static_cast<uint32_t>(_playerEntity) << RESET
              << std::endl;
}

udp::endpoint PlayerSession::endpoint() const
{
    return endpoint_;
}

entt::entity PlayerSession::getPlayerEntity() const
{
    return _playerEntity;
}
