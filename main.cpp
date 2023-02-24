#include "game.h"

int main()
{
    MainGame game;

    while (game.is_running())
    {
        game.update();
        game.events();
        game.display();
        game.delay();
    }
    return EXIT_SUCCESS;
}