#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "matrix.h"

enum class game_status
{
    STATUS_PLAYING,
    STATUS_FAILURE,
    STATUS_SUCCESS,
    STATUS_EXIT
};

class terminal_window
{
    private:
        static constexpr int DELAY_USEC = 10000;
        static constexpr int KEY_ESC = 27;
        static constexpr int KEY_SPACE = 32;
        static constexpr int INFO_MARGIN = 1;

    private:
        game_status status;
        game_matrix matrix;
        point origin_point;

    private:
        int screen_width;
        int screen_height;

    private:
        void init_ncurses();
        void unset_ncurses();
        void resize_terminal();
        void init_game();
        void gameover();

    private:
        void print_border();
        void print_number();
        void print_info();

    public:
        terminal_window();
        ~terminal_window();

    public:
        bool is_running();
        void update();
        void events();
        void display();
        void delay();
};
#endif