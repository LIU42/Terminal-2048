#include "2048.h"

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
    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 0; y < TABLE_LARGE; y++)
        {
            table_data[x][y] = 0;
        }
    }
    status = PLAYING;
    add_number(INIT_NUM_COUNT);
}

void main_game::add_number(int count = 1)
{
    static point add_list[BLOCK_COUNT];
    static int add_list_length;

    for (int i = 0; i < count; i++)
    {
        for (int x = 0; x < TABLE_LARGE; x++)
        {
            for (int y = 0; y < TABLE_LARGE; y++)
            {
                if (table_data[x][y] == 0)
                {
                    add_list[add_list_length].x = x;
                    add_list[add_list_length].y = y;
                    add_list_length += 1;
                }
            }
        }
        if (add_list_length != 0)
        {
            int rand_index = rand() % add_list_length;
            int rand_x = add_list[rand_index].x;
            int rand_y = add_list[rand_index].y;

            table_data[rand_x][rand_y] = 2;
            add_list_length = 0;
        }
    }
}

void main_game::up_action()
{
    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 1; y < TABLE_LARGE; y++)
        {
            while (y > 0 && table_data[x][y] != 0)
            {
                if (table_data[x][y - 1] == 0)
                {
                    table_data[x][y - 1] = table_data[x][y];
                    table_data[x][y] = 0;
                    y -= 1;
                }
                else if (table_data[x][y] == table_data[x][y - 1])
                {
                    table_data[x][y - 1] *= 2;
                    table_data[x][y] = 0;
                    y -= 1;
                }
                else { break; }
            }
        }
    }
    add_number();
}

void main_game::down_action()
{
    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = TABLE_LARGE - 2; y >= 0; y--)
        {
            while (y < TABLE_LARGE - 1 && table_data[x][y] != 0)
            {
                if (table_data[x][y + 1] == 0)
                {
                    table_data[x][y + 1] = table_data[x][y];
                    table_data[x][y] = 0;
                    y += 1;
                }
                else if (table_data[x][y] == table_data[x][y + 1])
                {
                    table_data[x][y + 1] *= 2;
                    table_data[x][y] = 0;
                    y += 1;
                }
                else { break; }
            }
        }
    }
    add_number();
}

void main_game::left_action()
{
    for (int y = 0; y < TABLE_LARGE; y++)
    {
        for (int x = 1; x < TABLE_LARGE; x++)
        {
            while (x > 0 && table_data[x][y] != 0)
            {
                if (table_data[x - 1][y] == 0)
                {
                    table_data[x - 1][y] = table_data[x][y];
                    table_data[x][y] = 0;
                    x -= 1;
                }
                else if (table_data[x][y] == table_data[x - 1][y])
                {
                    table_data[x - 1][y] *= 2;
                    table_data[x][y] = 0;
                    x -= 1;
                }
                else { break; }
            }
        }
    }
    add_number();
}

void main_game::right_action()
{
    for (int y = 0; y < TABLE_LARGE; y++)
    {
        for (int x = TABLE_LARGE - 2; x >= 0; x--)
        {
            while (x < TABLE_LARGE - 1 && table_data[x][y] != 0)
            {
                if (table_data[x + 1][y] == 0)
                {
                    table_data[x + 1][y] = table_data[x][y];
                    table_data[x][y] = 0;
                    x += 1;
                }
                else if (table_data[x][y] == table_data[x + 1][y])
                {
                    table_data[x + 1][y] *= 2;
                    table_data[x][y] = 0;
                    x += 1;
                }
                else { break; }
            }
        }
    }
    add_number();
}

void main_game::gameover()
{
    bool is_lose = true;
    bool is_win = false;

    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 0; y < TABLE_LARGE; y++)
        {
            if (table_data[x][y] != 2048)
            {
                if (table_data[x][y] != 0)
                {
                    if (y > 0 && table_data[x][y] == table_data[x][y - 1]) { is_lose = false; }
                    if (x > 0 && table_data[x][y] == table_data[x - 1][y]) { is_lose = false; }
                    if (y < TABLE_LARGE - 1 && table_data[x][y] == table_data[x][y + 1]) { is_lose = false; }
                    if (x < TABLE_LARGE - 1 && table_data[x][y] == table_data[x + 1][y]) { is_lose = false; }
                }
                else { is_lose = false; }
            }
            else { is_win = true; }
        }
    }
    if (is_lose) { status = OVER; }
    if (is_win) { status = WIN; }
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
                case KEY_UP: up_action(); break;
                case KEY_DOWN: down_action(); break;
                case KEY_LEFT: left_action(); break;
                case KEY_RIGHT: right_action(); break;
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

    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 0; y < TABLE_LARGE; y++)
        {
            int num = table_data[x][y];
            int length = 0;

            while (num > 0)
            {
                num = num / 10;
                length += 1;
            }
            switch (length)
            {
                case 1:  sprintf(number_text, "   %d  ", table_data[x][y]); break;
                case 2:  sprintf(number_text, "  %d  ", table_data[x][y]); break;
                case 3:  sprintf(number_text, "  %d ", table_data[x][y]); break;
                case 4:  sprintf(number_text, " %d ", table_data[x][y]); break;
                default: sprintf(number_text, " "); break;
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
        case OVER: mvaddstr(origin.y + TABLE_HEIGHT - INFO_MARGIN, origin.x, "Gameover!"); break;
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