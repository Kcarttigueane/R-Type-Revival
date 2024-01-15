#if !defined(LOBBY_HPP)
#    define LOBBY_HPP

#    include <string>

struct LobbyComponent {
    std::string usernameEntity;
    std::string ipEntity;
    std::string portEntity;
};

#endif  // LOBBY_HPP