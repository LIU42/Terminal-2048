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
        Point originPoint;

    private:
        int screenWidth;
        int screenHeight;

    private:
        void setCurses();
        void unsetCurses();
        void resizeTerminal();
        void initGame();
        void gameover();

    private:
        void displayBorder();
        void displayNumber();
        void displayInfo();

    public:
        MainGame();
        ~MainGame();

    public:
        bool isRunning();
        void update();
        void events();
        void display();
        void delay();
};
#endif