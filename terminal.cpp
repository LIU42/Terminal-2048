#include "terminal.h"

void MainGame::setWindow()
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
}

void MainGame::unsetWindow()
{
    nocbreak();
    keypad(stdscr, true);
    curs_set(true);
    echo();
    endwin();
}

void MainGame::resizeWindow()
{
    screenWidth = COLS;
    screenHeight = LINES;
    keyCode = 0;
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
    origin.x = (screenWidth - Matrix::MATRIX_WIDTH) / 2;
    origin.y = (screenHeight - Matrix::MATRIX_HEIGHT) / 2;

    for (int line = 0; line < Matrix::MATRIX_HEIGHT; line++)
    {
        switch (line % 4)
        {
            case 0:  mvaddstr(origin.y + line, origin.x, "+------+------+------+------+"); break;
            default: mvaddstr(origin.y + line, origin.x, "|      |      |      |      |"); break;
        }
    }
}

void MainGame::displayNumber()
{
    static char numberText[TEXT_LENGTH];

    origin.x += Matrix::NUMBER_INIT_X;
    origin.y += Matrix::NUMBER_INIT_Y;

    for (int x = 0; x < Matrix::MATRIX_LARGE; x++)
    {
        for (int y = 0; y < Matrix::MATRIX_LARGE; y++)
        {
            int num = matrix.getNumber(x, y);
            int length = 0;

            while (num > 0)
            {
                num /= 10;
                length += 1;
            }
            switch (length)
            {
                case 4: sprintf(numberText, " %d ", matrix.getNumber(x, y)); break;
                case 3: sprintf(numberText, "  %d ", matrix.getNumber(x, y)); break;
                case 2: sprintf(numberText, "  %d  ", matrix.getNumber(x, y)); break;
                case 1: sprintf(numberText, "   %d  ", matrix.getNumber(x, y)); break;
                case 0: sprintf(numberText, " "); break;
            }
            mvaddstr(origin.y + y * Matrix::BLOCK_HEIGHT, origin.x + x * Matrix::BLOCK_WIDTH, numberText);
        }
    }
}

void MainGame::displayInfo()
{
    switch (status)
    {
        case WIN:  mvaddstr(origin.y + Matrix::MATRIX_HEIGHT - INFO_MARGIN, origin.x, "You Win!"); break;
        case LOSE: mvaddstr(origin.y + Matrix::MATRIX_HEIGHT - INFO_MARGIN, origin.x, "Gameover!"); break;
        case EXIT: mvaddstr(origin.y + Matrix::MATRIX_HEIGHT - INFO_MARGIN, origin.x, "Exit."); break;
    }
    mvaddstr(origin.y - Matrix::BLOCK_HEIGHT, origin.x, "Welcome to 2048 in Terminal!");
}

MainGame::MainGame()
{
    srand((unsigned)time(NULL));
    setWindow();
    initGame();
}

MainGame::~MainGame()
{
    unsetWindow();
}

bool MainGame::isRunning()
{
    return status != EXIT;
}

void MainGame::update()
{
    resizeWindow();
    gameover();
}

void MainGame::events()
{
    keyCode = getch();

    if (keyCode == KEY_ESC) { status = EXIT; }

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
    if (status != EXIT && keyCode == KEY_SPACE) { initGame(); }
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