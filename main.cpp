#include "terminal2048.h"

MainGame game;

int main()
{
    srand((unsigned)time(NULL));
    
    game.setWindow();
    game.initGame();

    while (game.status != EXIT)
    {
        game.resizeWindow();
        game.gameover();
        game.events();
        game.display();
        usleep(GAME_DELAY);
    }
    game.unsetWindow();
    return 0;
}