#ifndef __TABLE_H__
#define __TABLE_H__

#include <stdlib.h>

struct point
{
    int x;
    int y;
};

class tables
{
    public:
        static const int TABLE_LARGE = 4;
        static const int BLOCK_COUNT = 16;

    private:
        int data[TABLE_LARGE][TABLE_LARGE];

    public:
        int get_data(int, int);

    public:
        void init_data();
        void add_number();
        void up_action();
        void down_action();
        void left_action();
        void right_action();

    public:
        bool is_win();
        bool is_lose();
};
#endif