#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>

struct Point
{
    int x;
    int y;
};

class Matrix
{
    public:
        static const int MATRIX_WIDTH = 29;
        static const int MATRIX_HEIGHT = 17;
        static const int MATRIX_LARGE = 4;

    public:
        static const int BLOCK_WIDTH = 7;
        static const int BLOCK_HEIGHT = 4;
        static const int BLOCK_COUNT = 16;

    public:
        static const int NUMBER_INIT_X = 1;
        static const int NUMBER_INIT_Y = 2;

    private:
        int numbers[MATRIX_LARGE][MATRIX_LARGE];

    public:
        int getNumber(int, int);

    public:
        void initNumbers();
        void addNumber();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

    public:
        bool isWin();
        bool isLose();
};
#endif