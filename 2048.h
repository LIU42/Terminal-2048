#ifndef __2048_H__
#define __2048_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

struct point
{
    int x;
    int y;
};

enum status_enum { PLAYING, OVER, WIN, EXIT };

class main_game
{
    public:
        static const int TABLE_WIDTH = 29;
        static const int TABLE_HEIGHT = 17;
        static const int TABLE_LARGE = 4;
        static const int DELAY_USEC = 10000;

    public:
        static const int BLOCK_COUNT = 16;
        static const int BLOCK_WIDTH = 7;
        static const int BLOCK_HEIGHT = 4;

    public:
        static const int KEY_ESC = 27;
        static const int KEY_SPACE = 32;
        static const int TEXT_LENGTH = 30;
        static const int INIT_NUM_COUNT = 2;

    public:
        static const int NUMBER_INIT_X = 1;
        static const int NUMBER_INIT_Y = 2;
        static const int INFO_MARGIN = 1;

    private:
        int table_data[TABLE_LARGE][TABLE_LARGE];
        int screen_width;
        int screen_height;
        int key_code;
        status_enum status;
        point origin;

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
        void add_number(int);
        void up_action();
        void down_action();
        void left_action();
        void right_action();
        void display_table();
        void display_number();
        void display_info();
};
#endif