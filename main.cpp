#include "2048.h"

main_game game;

int main()
{
    srand((unsigned)time(NULL));
    
    game.set_window();
    game.init_game();

    while (game.status != EXIT)
    {
        game.resize_window();
        game.gameover();
        game.events();
        game.display();
        usleep(GAME_DELAY_USEC);
    }
    game.unset_window();
    return 0;
}