#include "game.h"

int main()
{
    MainGame game;

    srand((unsigned)time(NULL));
    
    game.set_window();
    game.init_game();

    while (game.is_running())
    {
        game.resize_window();
        game.gameover();
        game.events();
        game.display();
        usleep(game.DELAY_USEC);
    }
    game.unset_window();
    return 0;
}