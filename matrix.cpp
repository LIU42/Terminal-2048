#include "matrix.h"

int Matrix::get_number(int x, int y)
{
    return numbers[x][y];
}

void Matrix::init_numbers()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            numbers[x][y] = 0;
        }
    }
}

void Matrix::add_number()
{
    static Point add_list[BLOCK_COUNT];
    static int add_list_length;

    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            if (numbers[x][y] == 0)
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

        numbers[rand_x][rand_y] = 2;
        add_list_length = 0;
    }
}

void Matrix::move_up()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 1; y < MATRIX_LARGE; y++)
        {
            while (y > 0 && numbers[x][y] != 0)
            {
                if (numbers[x][y - 1] == 0)
                {
                    numbers[x][y - 1] = numbers[x][y];
                    numbers[x][y] = 0;
                    y -= 1;
                }
                else if (numbers[x][y] == numbers[x][y - 1])
                {
                    numbers[x][y - 1] *= 2;
                    numbers[x][y] = 0;
                    y -= 1;
                }
                else { break; }
            }
        }
    }
}

void Matrix::move_down()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = MATRIX_LARGE - 2; y >= 0; y--)
        {
            while (y < MATRIX_LARGE - 1 && numbers[x][y] != 0)
            {
                if (numbers[x][y + 1] == 0)
                {
                    numbers[x][y + 1] = numbers[x][y];
                    numbers[x][y] = 0;
                    y += 1;
                }
                else if (numbers[x][y] == numbers[x][y + 1])
                {
                    numbers[x][y + 1] *= 2;
                    numbers[x][y] = 0;
                    y += 1;
                }
                else { break; }
            }
        }
    }
}

void Matrix::move_left()
{
    for (int y = 0; y < MATRIX_LARGE; y++)
    {
        for (int x = 1; x < MATRIX_LARGE; x++)
        {
            while (x > 0 && numbers[x][y] != 0)
            {
                if (numbers[x - 1][y] == 0)
                {
                    numbers[x - 1][y] = numbers[x][y];
                    numbers[x][y] = 0;
                    x -= 1;
                }
                else if (numbers[x][y] == numbers[x - 1][y])
                {
                    numbers[x - 1][y] *= 2;
                    numbers[x][y] = 0;
                    x -= 1;
                }
                else { break; }
            }
        }
    }
}

void Matrix::move_right()
{
    for (int y = 0; y < MATRIX_LARGE; y++)
    {
        for (int x = MATRIX_LARGE - 2; x >= 0; x--)
        {
            while (x < MATRIX_LARGE - 1 && numbers[x][y] != 0)
            {
                if (numbers[x + 1][y] == 0)
                {
                    numbers[x + 1][y] = numbers[x][y];
                    numbers[x][y] = 0;
                    x += 1;
                }
                else if (numbers[x][y] == numbers[x + 1][y])
                {
                    numbers[x + 1][y] *= 2;
                    numbers[x][y] = 0;
                    x += 1;
                }
                else { break; }
            }
        }
    }
}

bool Matrix::is_win()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            if (numbers[x][y] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

bool Matrix::is_lose()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            if (numbers[x][y] != 0)
            {
                if (y > 0 && numbers[x][y] == numbers[x][y - 1]) { return false; }
                if (x > 0 && numbers[x][y] == numbers[x - 1][y]) { return false; }
                if (y < MATRIX_LARGE - 1 && numbers[x][y] == numbers[x][y + 1]) { return false; }
                if (x < MATRIX_LARGE - 1 && numbers[x][y] == numbers[x + 1][y]) { return false; }
            }
            else { return false; }
        }
    }
    return true;
}