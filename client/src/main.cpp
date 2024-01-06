#include "../include/command_line_arguments.hpp"
#include "../include/managers/game_manager.hpp"
#include "../src/network/payload.pb.h"

int main(int argc, char* argv[])
{
    CommandLineArgs args;
    if (!args.parse_command_line_arguments(argc, argv)) {
        return 0;
    }

    GameManager game_manager(args.ip_address, args.port);
    game_manager.start_game();

    return 0;
}
