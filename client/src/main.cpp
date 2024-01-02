#include "../include/command_line_arguments.hpp"
#include "../include/managers/game_manager.hpp"

int main(int argc, char* argv[])
{
    CommandLineArgs args;
    if (!args.parse(argc, argv)) {
        return 0;
    }

    GameManager game_manager(args.ip_address, args.port);
    game_manager.start_game();
    game_manager.game_loop();

    return 0;
}
