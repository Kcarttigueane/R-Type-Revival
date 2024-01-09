#include "../../include/managers/players_session_manager.hpp"

udp::endpoint PlayerSession::endpoint() const
{
    return endpoint_;
}

entt::entity PlayerSession::getPlayerEntity() const
{
    return _playerEntity;
}
