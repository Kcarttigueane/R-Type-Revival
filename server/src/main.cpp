#include "../include/managers/game_manager.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: ./r-type_server <address> <port>\n";
        return 1;
    }

    std::string server_address = argv[1];
    unsigned short port = std::stoi(argv[2]);

    GameManager game_manager(server_address, port);
    game_manager.run();
    return 0;
}
