#include "window.h"

void terminal_window::init_ncurses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
}

void terminal_window::unset_ncurses()
{
    nocbreak();
    keypad(stdscr, true);
    curs_set(true);
    echo();
    endwin();
}

void terminal_window::resize_terminal()
{
    screen_width = COLS;
    screen_height = LINES;
}

void terminal_window::init_game()
{
    status = game_status::STATUS_PLAYING;
    matrix.init_matrix();
    matrix.add_number();
    matrix.add_number();
}

void terminal_window::gameover()
{
    if (matrix.is_failure())
    {
        status = game_status::STATUS_FAILURE;
    }
    if (matrix.is_success())
    {
        status = game_status::STATUS_SUCCESS;
    }
}

void terminal_window::print_border()
{
    origin_point.x = (screen_width - game_matrix::MATRIX_WIDTH) / 2;
    origin_point.y = (screen_height - game_matrix::MATRIX_HEIGHT) / 2;

    for (int line = 0; line < game_matrix::MATRIX_HEIGHT; line++)
    {
        switch (line % 4)
        {
            case 0:  mvprintw(origin_point.y + line, origin_point.x, "+------+------+------+------+"); break;
            default: mvprintw(origin_point.y + line, origin_point.x, "|      |      |      |      |"); break;
        }
    }
}

void terminal_window::print_number()
{
    origin_point.x += game_matrix::NUMBER_INIT_X;
    origin_point.y += game_matrix::NUMBER_INIT_Y;

    for (int x = 0; x < game_matrix::MATRIX_LARGE; x++)
    {
        for (int y = 0; y < game_matrix::MATRIX_LARGE; y++)
        {
            int number_x = origin_point.x + x * game_matrix::BLOCK_WIDTH;
            int number_y = origin_point.y + y * game_matrix::BLOCK_HEIGHT;
            int number = matrix.get_number(x, y);

            if (number >= 1000)
            {
                mvprintw(number_y, number_x, " %d ", number);
            }
            else if (number >= 100)
            {
                mvprintw(number_y, number_x, "  %d ", number);
            }
            else if (number >= 10)
            {
                mvprintw(number_y, number_x, "  %d  ", number);
            }
            else if (number >= 1)
            {
                mvprintw(number_y, number_x, "   %d  ", number);
            }
        }
    }
}

void terminal_window::print_info()
{
    int info_x = origin_point.x;
    int info_y = origin_point.y + game_matrix::MATRIX_HEIGHT - INFO_MARGIN;

    switch (status)
    {
        case game_status::STATUS_SUCCESS: mvprintw(info_y, info_x, "You Win!"); break;
        case game_status::STATUS_FAILURE: mvprintw(info_y, info_x, "Gameover!"); break;
        case game_status::STATUS_EXIT: mvprintw(info_y, info_x, "Exit."); break;
    }
    mvprintw(origin_point.y - game_matrix::BLOCK_HEIGHT, origin_point.x, "Welcome to 2048 in Terminal!");
}

terminal_window::terminal_window(): origin_point(0, 0)
{
    srand((unsigned)time(NULL));
    init_ncurses();
    init_game();
}

terminal_window::~terminal_window()
{
    unset_ncurses();
}

bool terminal_window::is_running()
{
    return status != game_status::STATUS_EXIT;
}

void terminal_window::update()
{
    resize_terminal();
    gameover();
}

void terminal_window::events()
{
    int key_code = getch();

    if (key_code == KEY_ESC)
    {
        status = game_status::STATUS_EXIT;
    }
    else if (status != game_status::STATUS_EXIT && key_code == KEY_SPACE)
    {
        init_game();
    }
    else if (status == game_status::STATUS_PLAYING)
    {
        if (key_code == KEY_UP)
        {
            matrix.transform_up();
            matrix.add_number();
        }
        else if (key_code == KEY_DOWN)
        {
            matrix.transform_down();
            matrix.add_number();
        }
        else if (key_code == KEY_LEFT)
        {
            matrix.transform_left();
            matrix.add_number();
        }
        else if (key_code == KEY_RIGHT)
        {
            matrix.transform_right();
            matrix.add_number();
        }
    }
}

void terminal_window::display()
{
    clear();
    print_border();
    print_number();
    print_info();
    refresh();
}

void terminal_window::delay()
{
    usleep(DELAY_USEC);
}