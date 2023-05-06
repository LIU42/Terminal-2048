#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "matrix.h"

enum Status { PLAYING, LOSE, WIN, EXIT };

class MainGame
{
    private:
        static const int DELAY_USEC = 10000;
        static const int KEY_ESC = 27;
        static const int KEY_SPACE = 32;
        static const int TEXT_LENGTH = 30;
        static const int INFO_MARGIN = 1;

    private:
        Status status;
        Matrix matrix;
        Point origin;

    private:
        int screen_width;
        int screen_height;
        int key_code;

    private:
        void set_window();
        void unset_window();
        void resize_window();
        void init_game();
        void gameover();

    private:
        void display_border();
        void display_number();
        void display_info();

    public:
        MainGame();
        ~MainGame();

    public:
        bool is_running();
        void update();
        void events();
        void display();
        void delay();
};
#endif