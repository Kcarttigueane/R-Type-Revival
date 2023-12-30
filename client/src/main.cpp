#include <SFML/Graphics.hpp>
#include "../include/managers/game_manager.hpp"

int main(int argc, __attribute__((unused)) char* argv[])
{
    GameManager game_manager;
    game_manager.start_game();
    game_manager.game_loop();

    return 0;
}
