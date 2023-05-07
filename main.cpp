#include "terminal.h"

int main(int argc, char* argv[])
{
    MainGame game;

    while (game.isRunning())
    {
        game.update();
        game.events();
        game.display();
        game.delay();
    }
    return EXIT_SUCCESS;
}