#include "game.h"

void main_game::set_window()
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
}

void main_game::unset_window()
{
    nocbreak();
    keypad(stdscr, true);
    curs_set(true);
    echo();
    endwin();
}

void main_game::resize_window()
{
    screen_width = COLS;
    screen_height = LINES;
    key_code = 0;
}

bool main_game::is_running()
{
    return status != EXIT;
}

void main_game::init_game()
{
    status = PLAYING;
    table.init_data();
    table.add_number(INIT_NUM_COUNT);
}

void main_game::gameover()
{
    if (table.is_lose()) { status = LOSE; }
    if (table.is_win()) { status = WIN; }
}

void main_game::events()
{
    key_code = getch();

    if (key_code != 0)
    {
        if (key_code == KEY_ESC) { status = EXIT; }

        if (status == PLAYING)
        {
            switch (key_code)
            {
                case KEY_UP: table.up_action(); break;
                case KEY_DOWN: table.down_action(); break;
                case KEY_LEFT: table.left_action(); break;
                case KEY_RIGHT: table.right_action(); break;
            }
        }
        if (status != EXIT && key_code == KEY_SPACE) { init_game(); }
    }
}

void main_game::display_table()
{
    origin.x = (screen_width - TABLE_WIDTH) / 2;
    origin.y = (screen_height - TABLE_HEIGHT) / 2;

    for (int line = 0; line < TABLE_HEIGHT; line++)
    {
        switch (line % 4)
        {
            case 0:  mvaddstr(origin.y + line, origin.x, "+------+------+------+------+"); break;
            default: mvaddstr(origin.y + line, origin.x, "|      |      |      |      |"); break;
        }
    }
}

void main_game::display_number()
{
    static char number_text[TEXT_LENGTH];

    origin.x += NUMBER_INIT_X;
    origin.y += NUMBER_INIT_Y;

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
            mvaddstr(origin.y + y * BLOCK_HEIGHT, origin.x + x * BLOCK_WIDTH, number_text);
        }
    }
}

void main_game::display_info()
{
    switch (status)
    {
        case WIN:  mvaddstr(origin.y + TABLE_HEIGHT - INFO_MARGIN, origin.x, "You Win!"); break;
        case LOSE: mvaddstr(origin.y + TABLE_HEIGHT - INFO_MARGIN, origin.x, "Gameover!"); break;
        case EXIT: mvaddstr(origin.y + TABLE_HEIGHT - INFO_MARGIN, origin.x, "Exit."); break;
    }
    mvaddstr(origin.y - BLOCK_HEIGHT, origin.x, "Welcome to 2048 in Terminal!");
}

void main_game::display()
{
    erase();
    display_table();
    display_number();
    display_info();
    refresh();
}