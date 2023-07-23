#include "terminal.h"

void MainGame::setCurses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
}

void MainGame::unsetCurses()
{
    nocbreak();
    keypad(stdscr, true);
    curs_set(true);
    echo();
    endwin();
}

void MainGame::resizeTerminal()
{
    screenWidth = COLS;
    screenHeight = LINES;
}

void MainGame::initGame()
{
    status = PLAYING;
    matrix.initNumbers();
    matrix.addNumber();
    matrix.addNumber();
}

void MainGame::gameover()
{
    if (matrix.isLose()) { status = LOSE; }
    if (matrix.isWin()) { status = WIN; }
}

void MainGame::displayBorder()
{
    originPoint.x = (screenWidth - Matrix::MATRIX_WIDTH) / 2;
    originPoint.y = (screenHeight - Matrix::MATRIX_HEIGHT) / 2;

    for (int line = 0; line < Matrix::MATRIX_HEIGHT; line++)
    {
        switch (line % 4)
        {
            case 0:  mvaddstr(originPoint.y + line, originPoint.x, "+------+------+------+------+"); break;
            default: mvaddstr(originPoint.y + line, originPoint.x, "|      |      |      |      |"); break;
        }
    }
}

void MainGame::displayNumber()
{
    static char numberText[TEXT_LENGTH];

    originPoint.x += Matrix::NUMBER_INIT_X;
    originPoint.y += Matrix::NUMBER_INIT_Y;

    for (int x = 0; x < Matrix::MATRIX_LARGE; x++)
    {
        for (int y = 0; y < Matrix::MATRIX_LARGE; y++)
        {
            int number = matrix.getNumber(x, y);

            if (number >= 1000)
            {
                sprintf(numberText, " %d ", number);
            }
            else if (number >= 100)
            {
                sprintf(numberText, "  %d ", number);
            }
            else if (number >= 10)
            {
                sprintf(numberText, "  %d  ", number);
            }
            else if (number >= 1)
            {
                sprintf(numberText, "   %d  ", number);
            }
            else
            {
                sprintf(numberText, " "); 
            }
            mvaddstr(originPoint.y + y * Matrix::BLOCK_HEIGHT, originPoint.x + x * Matrix::BLOCK_WIDTH, numberText);
        }
    }
}

void MainGame::displayInfo()
{
    switch (status)
    {
        case WIN:  mvaddstr(originPoint.y + Matrix::MATRIX_HEIGHT - INFO_MARGIN, originPoint.x, "You Win!"); break;
        case LOSE: mvaddstr(originPoint.y + Matrix::MATRIX_HEIGHT - INFO_MARGIN, originPoint.x, "Gameover!"); break;
        case EXIT: mvaddstr(originPoint.y + Matrix::MATRIX_HEIGHT - INFO_MARGIN, originPoint.x, "Exit."); break;
    }
    mvaddstr(originPoint.y - Matrix::BLOCK_HEIGHT, originPoint.x, "Welcome to 2048 in Terminal!");
}

MainGame::MainGame()
{
    srand((unsigned)time(NULL));
    setCurses();
    initGame();
}

MainGame::~MainGame()
{
    unsetCurses();
}

bool MainGame::isRunning()
{
    return status != EXIT;
}

void MainGame::update()
{
    resizeTerminal();
    gameover();
}

void MainGame::events()
{
    int keyCode = getch();

    if (keyCode == KEY_ESC)
    {
        status = EXIT;
    }
    if (status != EXIT && keyCode == KEY_SPACE)
    {
        initGame();
    }
    if (status == PLAYING)
    {
        if (keyCode == KEY_UP)
        {
            matrix.moveUp();
            matrix.addNumber();
        }
        else if (keyCode == KEY_DOWN)
        {
            matrix.moveDown();
            matrix.addNumber();
        }
        else if (keyCode == KEY_LEFT)
        {
            matrix.moveLeft();
            matrix.addNumber();
        }
        else if (keyCode == KEY_RIGHT)
        {
            matrix.moveRight();
            matrix.addNumber();
        }
    }
}

void MainGame::display()
{
    erase();
    displayBorder();
    displayNumber();
    displayInfo();
    refresh();
}

void MainGame::delay()
{
    usleep(DELAY_USEC);
}