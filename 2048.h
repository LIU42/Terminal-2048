#ifndef __2048_H__
#define __2048_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "config.h"

struct point
{
    int x;
    int y;
};

class main_game
{
    public:
        int table_data[TABLE_LARGE][TABLE_LARGE];
        int screen_width;
        int screen_height;
        int key_code;
        int status;
        point origin;

    public:
        void set_window();
        void unset_window();
        void resize_window();

    public:
        void init_game();
        void add_number(int);
        void gameover();
        void events();
        void display_table();
        void display_number();
        void display_info();
        void display();
    
    public:
        void up_action();
        void down_action();
        void left_action();
        void right_action();
};

extern main_game game;
#endif