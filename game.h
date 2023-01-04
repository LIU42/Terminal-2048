#ifndef __GAME_H__
#define __GAME_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "table.h"

enum Status { PLAYING, LOSE, WIN, EXIT };

class MainGame
{
    public:
        static const int DELAY_USEC = 10000;
        static const int KEY_ESC = 27;
        static const int KEY_SPACE = 32;
        static const int TEXT_LENGTH = 30;
        static const int INFO_MARGIN = 1;

    private:
        Status status;
        Table table;
        Point origin;

    private:
        int screen_width;
        int screen_height;
        int key_code;

    public:
        void set_window();
        void unset_window();
        void resize_window();
        void init_game();

    public:
        bool is_running();
        void gameover();
        void events();
        void display();

    private:
        void display_table();
        void display_number();
        void display_info();
};
#endif