#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>
#include <memory.h>
#include <vector>

using namespace std;

class point
{
    public:
        int x;
        int y;

    public:
        point(int x, int y);
};

class game_matrix
{
    public:
        static constexpr int MATRIX_WIDTH = 29;
        static constexpr int MATRIX_HEIGHT = 17;
        static constexpr int MATRIX_LARGE = 4;

    public:
        static constexpr int BLOCK_WIDTH = 7;
        static constexpr int BLOCK_HEIGHT = 4;
        static constexpr int BLOCK_COUNT = 16;

    public:
        static constexpr int NUMBER_INIT_X = 1;
        static constexpr int NUMBER_INIT_Y = 2;

    private:
        int number_matrix[MATRIX_LARGE][MATRIX_LARGE];

    public:
        int get_number(int x, int y);

    public:
        void init_matrix();
        void add_number();
        void transform_up();
        void transform_down();
        void transform_left();
        void transform_right();

    public:
        bool is_success();
        bool is_failure();
};
#endif