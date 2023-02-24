#include "game.h"

void MainGame::set_window()
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
}

void MainGame::unset_window()
{
    nocbreak();
    keypad(stdscr, true);
    curs_set(true);
    echo();
    endwin();
}

void MainGame::resize_window()
{
    screen_width = COLS;
    screen_height = LINES;
    key_code = 0;
}

void MainGame::init_game()
{
    status = PLAYING;
    table.init_data();
    table.add_number();
    table.add_number();
}

void MainGame::gameover()
{
    if (table.is_lose()) { status = LOSE; }
    if (table.is_win()) { status = WIN; }
}

void MainGame::display_table()
{
    origin.x = (screen_width - table.TABLE_WIDTH) / 2;
    origin.y = (screen_height - table.TABLE_HEIGHT) / 2;

    for (int line = 0; line < table.TABLE_HEIGHT; line++)
    {
        switch (line % 4)
        {
            case 0:  mvaddstr(origin.y + line, origin.x, "+------+------+------+------+"); break;
            default: mvaddstr(origin.y + line, origin.x, "|      |      |      |      |"); break;
        }
    }
}

void MainGame::display_number()
{
    static char number_text[TEXT_LENGTH];

    origin.x += table.NUMBER_INIT_X;
    origin.y += table.NUMBER_INIT_Y;

    for (int x = 0; x < table.TABLE_LARGE; x++)
    {
        for (int y = 0; y < table.TABLE_LARGE; y++)
        {
            int num = table.get_data(x, y);

            if (num > 1000)
            {
                sprintf(number_text, " %d ", num);
            }
            else if (num > 100)
            {
                sprintf(number_text, "  %d ", num);
            }
            else if (num > 10)
            {
                sprintf(number_text, "  %d  ", num);
            }
            else if (num > 1)
            {
                sprintf(number_text, "   %d  ", num);
            }
            else
            {
                sprintf(number_text, " ");
            }
            mvaddstr(origin.y + y * table.BLOCK_HEIGHT, origin.x + x * table.BLOCK_WIDTH, number_text);
        }
    }
}

void MainGame::display_info()
{
    switch (status)
    {
        case WIN:  mvaddstr(origin.y + table.TABLE_HEIGHT - INFO_MARGIN, origin.x, "You Win!"); break;
        case LOSE: mvaddstr(origin.y + table.TABLE_HEIGHT - INFO_MARGIN, origin.x, "Gameover!"); break;
        case EXIT: mvaddstr(origin.y + table.TABLE_HEIGHT - INFO_MARGIN, origin.x, "Exit."); break;
    }
    mvaddstr(origin.y - table.BLOCK_HEIGHT, origin.x, "Welcome to 2048 in Terminal!");
}

MainGame::MainGame()
{
    srand((unsigned)time(NULL));
    set_window();
    init_game();
}

MainGame::~MainGame()
{
    unset_window();
}

bool MainGame::is_running()
{
    return status != EXIT;
}

void MainGame::update()
{
    resize_window();
    gameover();
}

void MainGame::events()
{
    key_code = getch();

    if (key_code != 0)
    {
        if (key_code == KEY_ESC) { status = EXIT; }

        if (status == PLAYING)
        {
            if (key_code == KEY_UP)
            {
                table.move_up();
                table.add_number();
            }
            else if (key_code == KEY_DOWN)
            {
                table.move_down();
                table.add_number();
            }
            else if (key_code == KEY_LEFT)
            {
                table.move_left();
                table.add_number();
            }
            else if (key_code == KEY_RIGHT)
            {
                table.move_right();
                table.add_number();
            }
        }
        if (status != EXIT && key_code == KEY_SPACE) { init_game(); }
    }
}

void MainGame::display()
{
    erase();
    display_table();
    display_number();
    display_info();
    refresh();
}

void MainGame::delay()
{
    usleep(DELAY_USEC);
}