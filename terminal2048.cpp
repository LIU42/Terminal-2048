#include "terminal2048.h"

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
    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 0; y < TABLE_LARGE; y++)
        {
            tableData[x][y] = 0;
        }
    }
    status = PLAYING;
    addNumber(INIT_NUM_COUNT);
}

void MainGame::addNumber(int count = 1)
{
    Point addList[BLOCK_COUNT];
    int addListLength = 0;
    
    for (int i = 0; i < count; i++)
    {
        for (int x = 0; x < TABLE_LARGE; x++)
        {
            for (int y = 0; y < TABLE_LARGE; y++)
            {
                if (tableData[x][y] == 0)
                {
                    addList[addListLength].x = x;
                    addList[addListLength].y = y;
                    addListLength += 1;
                }
            }
        }
        if (addListLength != 0)
        {
            int randIndex = rand() % addListLength;
            tableData[addList[randIndex].x][addList[randIndex].y] = 2;
            addListLength = 0;
        }
    }
}

void MainGame::upAction()
{
    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 1; y < TABLE_LARGE; y++)
        {
            while (y > 0 && tableData[x][y] != 0)
            {
                if (tableData[x][y - 1] == 0)
                {
                    tableData[x][y - 1] = tableData[x][y];
                    tableData[x][y] = 0;
                    y -= 1;
                }
                else if (tableData[x][y] == tableData[x][y - 1])
                {
                    tableData[x][y - 1] *= 2;
                    tableData[x][y] = 0;
                    y -= 1;
                }
                else { break; }
            }
        }
    }
    addNumber();
}

void MainGame::downAction()
{
    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = TABLE_LARGE - 2; y >= 0; y--)
        {
            while (y < TABLE_LARGE - 1 && tableData[x][y] != 0)
            {
                if (tableData[x][y + 1] == 0)
                {
                    tableData[x][y + 1] = tableData[x][y];
                    tableData[x][y] = 0;
                    y += 1;
                }
                else if (tableData[x][y] == tableData[x][y + 1])
                {
                    tableData[x][y + 1] *= 2;
                    tableData[x][y] = 0;
                    y += 1;
                }
                else { break; }
            }
        }
    }
    addNumber();
}

void MainGame::leftAction()
{
    for (int y = 0; y < TABLE_LARGE; y++)
    {
        for (int x = 1; x < TABLE_LARGE; x++)
        {
            while (x > 0 && tableData[x][y] != 0)
            {
                if (tableData[x - 1][y] == 0)
                {
                    tableData[x - 1][y] = tableData[x][y];
                    tableData[x][y] = 0;
                    x -= 1;
                }
                else if (tableData[x][y] == tableData[x - 1][y])
                {
                    tableData[x - 1][y] *= 2;
                    tableData[x][y] = 0;
                    x -= 1;
                }
                else { break; }
            }
        }
    }
    addNumber();
}

void MainGame::rightAction()
{
    for (int y = 0; y < TABLE_LARGE; y++)
    {
        for (int x = TABLE_LARGE - 2; x >= 0; x--)
        {
            while (x < TABLE_LARGE - 1 && tableData[x][y] != 0)
            {
                if (tableData[x + 1][y] == 0)
                {
                    tableData[x + 1][y] = tableData[x][y];
                    tableData[x][y] = 0;
                    x += 1;
                }
                else if (tableData[x][y] == tableData[x + 1][y])
                {
                    tableData[x + 1][y] *= 2;
                    tableData[x][y] = 0;
                    x += 1;
                }
                else { break; }
            }
        }
    }
    addNumber();
}

void MainGame::gameover()
{
    bool isLose = true;
    bool isWin = false;

    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 0; y < TABLE_LARGE; y++)
        {
            if (tableData[x][y] != 2048)
            {
                if (tableData[x][y] != 0)
                {
                    if (y > 0 && tableData[x][y] == tableData[x][y - 1]) { isLose = false; }
                    if (x > 0 && tableData[x][y] == tableData[x - 1][y]) { isLose = false; }
                    if (y < TABLE_LARGE - 1 && tableData[x][y] == tableData[x][y + 1]) { isLose = false; }
                    if (x < TABLE_LARGE - 1 && tableData[x][y] == tableData[x + 1][y]) { isLose = false; }
                }
                else { isLose = false; }
            }
            else { isWin = true; }
        }
    }
    if (isLose) { status = OVER; }
    if (isWin) { status = WIN; }
}

void MainGame::events()
{
    keyCode = getch();

    if (keyCode != 0)
    {
        if (keyCode == KEY_ESC) { status = EXIT; }

        if (status == PLAYING)
        {
            switch (keyCode)
            {
                case KEY_UP: upAction(); break;
                case KEY_DOWN: downAction(); break;
                case KEY_LEFT: leftAction(); break;
                case KEY_RIGHT: rightAction(); break;
            }
        }
        else if (status != EXIT && keyCode == KEY_SPACE) { initGame(); }
    }
}

void MainGame::displayTable()
{
    origin.x = (screenWidth - TABLE_WIDTH) / 2;
    origin.y = (screenHeight - TABLE_HEIGHT) / 2;

    for (int line = 0; line < TABLE_HEIGHT; line++)
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
    char numberText[TEXT_LENGTH];

    origin.x += NUMBER_INIT_X;
    origin.y += NUMBER_INIT_Y;

    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 0; y < TABLE_LARGE; y++)
        {
            int num = tableData[x][y];
            int length = 0;

            while (num > 0)
            {
                num = num / 10;
                length += 1;
            }
            switch (length)
            {
                case 1:  sprintf(numberText, "   %d  ", tableData[x][y]); break;
                case 2:  sprintf(numberText, "  %d  ", tableData[x][y]); break;
                case 3:  sprintf(numberText, "  %d ", tableData[x][y]); break;
                case 4:  sprintf(numberText, " %d ", tableData[x][y]); break;
                default: sprintf(numberText, " "); break;
            }
            mvaddstr(origin.y + y * BLOCK_HEIGHT, origin.x + x * BLOCK_WIDTH, numberText);
        }
    }
}

void MainGame::displayInfo()
{
    switch (status)
    {
        case WIN:  mvaddstr(origin.y + TABLE_HEIGHT - INFO_MARGIN, origin.x, "You Win!"); break;
        case OVER: mvaddstr(origin.y + TABLE_HEIGHT - INFO_MARGIN, origin.x, "Gameover!"); break;
        case EXIT: mvaddstr(origin.y + TABLE_HEIGHT - INFO_MARGIN, origin.x, "Exit."); break;
    }
    mvaddstr(origin.y - BLOCK_HEIGHT, origin.x, "Welcome to 2048 in Terminal!");
}

void MainGame::display()
{
    erase();
    displayTable();
    displayNumber();
    displayInfo();
    refresh();
}