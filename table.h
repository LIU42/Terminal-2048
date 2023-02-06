#ifndef __TABLE_H__
#define __TABLE_H__

#include <stdlib.h>

struct Point
{
    int x;
    int y;
};

class Table
{
    public:
        static const int TABLE_WIDTH = 29;
        static const int TABLE_HEIGHT = 17;
        static const int TABLE_LARGE = 4;

    public:
        static const int BLOCK_WIDTH = 7;
        static const int BLOCK_HEIGHT = 4;
        static const int BLOCK_COUNT = 16;

    public:
        static const int NUMBER_INIT_X = 1;
        static const int NUMBER_INIT_Y = 2;

    private:
        int data[TABLE_LARGE][TABLE_LARGE];

    public:
        int get_data(int, int);

    public:
        void init_data();
        void add_number();
        void move_up();
        void move_down();
        void move_left();
        void move_right();

    public:
        bool is_win();
        bool is_lose();
};
#endif