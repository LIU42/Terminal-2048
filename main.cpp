#include "game.h"

int main(int argc, char* argv[])
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