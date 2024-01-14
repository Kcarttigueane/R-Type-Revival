#include "../../common/command_line_arguments/command_line_arguments.hpp"
#include "../include/managers/game_manager.hpp"

int main(int argc, char* argv[])
{
    CommandLineArgs args;
    if (!args.parse_command_line_arguments(argc, argv)) {
        return 0;
    }

    boost::asio::io_service io_service;

    GameManager game_manager(args._ip_address, args._port, io_service);
    game_manager.start_game();

    return 0;
}
