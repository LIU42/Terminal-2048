#ifndef __TERMINAL2048_H__
#define __TERMINAL2048_H__

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "config.h"

struct Point
{
    int x;
    int y;
};

class MainGame
{
    public:
        int tableData[TABLE_LARGE][TABLE_LARGE];
        int screenWidth;
        int screenHeight;
        int keyCode;
        int status;
        Point origin;

    public:
        void setWindow();
        void unsetWindow();
        void resizeWindow();

    public:
        void initGame();
        void addNumber(int);
        void gameover();
        void events();
        void displayTable();
        void displayNumber();
        void displayInfo();
        void display();
    
    public:
        void upAction();
        void downAction();
        void leftAction();
        void rightAction();
};

extern MainGame game;
#endif