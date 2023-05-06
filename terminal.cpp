#include "terminal.h"

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
    matrix.init_numbers();
    matrix.add_number();
    matrix.add_number();
}

void MainGame::gameover()
{
    if (matrix.is_lose()) { status = LOSE; }
    if (matrix.is_win()) { status = WIN; }
}

void MainGame::display_border()
{
    origin.x = (screen_width - matrix.MATRIX_WIDTH) / 2;
    origin.y = (screen_height - matrix.MATRIX_HEIGHT) / 2;

    for (int line = 0; line < matrix.MATRIX_HEIGHT; line++)
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

    origin.x += matrix.NUMBER_INIT_X;
    origin.y += matrix.NUMBER_INIT_Y;

    for (int x = 0; x < matrix.MATRIX_LARGE; x++)
    {
        for (int y = 0; y < matrix.MATRIX_LARGE; y++)
        {
            int num = matrix.get_number(x, y);

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
            mvaddstr(origin.y + y * matrix.BLOCK_HEIGHT, origin.x + x * matrix.BLOCK_WIDTH, number_text);
        }
    }
}

void MainGame::display_info()
{
    switch (status)
    {
        case WIN:  mvaddstr(origin.y + matrix.MATRIX_HEIGHT - INFO_MARGIN, origin.x, "You Win!"); break;
        case LOSE: mvaddstr(origin.y + matrix.MATRIX_HEIGHT - INFO_MARGIN, origin.x, "Gameover!"); break;
        case EXIT: mvaddstr(origin.y + matrix.MATRIX_HEIGHT - INFO_MARGIN, origin.x, "Exit."); break;
    }
    mvaddstr(origin.y - matrix.BLOCK_HEIGHT, origin.x, "Welcome to 2048 in Terminal!");
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
                matrix.move_up();
                matrix.add_number();
            }
            else if (key_code == KEY_DOWN)
            {
                matrix.move_down();
                matrix.add_number();
            }
            else if (key_code == KEY_LEFT)
            {
                matrix.move_left();
                matrix.add_number();
            }
            else if (key_code == KEY_RIGHT)
            {
                matrix.move_right();
                matrix.add_number();
            }
        }
        if (status != EXIT && key_code == KEY_SPACE) { init_game(); }
    }
}

void MainGame::display()
{
    erase();
    display_border();
    display_number();
    display_info();
    refresh();
}

void MainGame::delay()
{
    usleep(DELAY_USEC);
}