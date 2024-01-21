#include "matrix.h"

point::point(int x, int y)
{
    this->x = x;
    this->y = y;
}

int game_matrix::get_number(int x, int y)
{
    return number_matrix[x][y];
}

void game_matrix::init_matrix()
{
    memset(number_matrix, 0, sizeof(number_matrix));
}

void game_matrix::add_number()
{
    vector<point> available_points;

    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            if (number_matrix[x][y] == 0)
            {
                available_points.emplace_back(point(x, y));
            }
        }
    }
    if (!available_points.empty())
    {
        int random_index = rand() % available_points.size();
        int rand_x = available_points[random_index].x;
        int rand_y = available_points[random_index].y;
        number_matrix[rand_x][rand_y] = 2;
    }
}

void game_matrix::transform_up()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 1; y < MATRIX_LARGE; y++)
        {
            for (int i = y; i > 0 && number_matrix[x][i] != 0; i--)
            {
                if (number_matrix[x][i - 1] == 0)
                {
                    number_matrix[x][i - 1] = number_matrix[x][i];
                    number_matrix[x][i] = 0;
                    continue;
                }
                if (number_matrix[x][i] == number_matrix[x][i - 1])
                {
                    number_matrix[x][i - 1] *= 2;
                    number_matrix[x][i] = 0;
                    continue;
                }
                break;
            }
        }
    }
}

void game_matrix::transform_down()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = MATRIX_LARGE - 2; y >= 0; y--)
        {
            for (int i = y; i < MATRIX_LARGE - 1 && number_matrix[x][i] != 0; i++)
            {
                if (number_matrix[x][i + 1] == 0)
                {
                    number_matrix[x][i + 1] = number_matrix[x][i];
                    number_matrix[x][i] = 0;
                    continue;
                }
                if (number_matrix[x][i] == number_matrix[x][i + 1])
                {
                    number_matrix[x][i + 1] *= 2;
                    number_matrix[x][i] = 0;
                    continue;
                }
                break;
            }
        }
    }
}

void game_matrix::transform_left()
{
    for (int y = 0; y < MATRIX_LARGE; y++)
    {
        for (int x = 1; x < MATRIX_LARGE; x++)
        {
            for (int i = x; i > 0 && number_matrix[i][y] != 0; i--)
            {
                if (number_matrix[i - 1][y] == 0)
                {
                    number_matrix[i - 1][y] = number_matrix[i][y];
                    number_matrix[i][y] = 0;
                    continue;
                }
                if (number_matrix[i][y] == number_matrix[i - 1][y])
                {
                    number_matrix[i - 1][y] *= 2;
                    number_matrix[i][y] = 0;
                    continue;
                }
                break;
            }
        }
    }
}

void game_matrix::transform_right()
{
    for (int y = 0; y < MATRIX_LARGE; y++)
    {
        for (int x = MATRIX_LARGE - 2; x >= 0; x--)
        {
            for (int i = x; i < MATRIX_LARGE - 1 && number_matrix[i][y] != 0; i++)
            {
                if (number_matrix[i + 1][y] == 0)
                {
                    number_matrix[i + 1][y] = number_matrix[i][y];
                    number_matrix[i][y] = 0;
                    continue;
                }
                if (number_matrix[i][y] == number_matrix[i + 1][y])
                {
                    number_matrix[i + 1][y] *= 2;
                    number_matrix[i][y] = 0;
                    continue;
                }
                break;
            }
        }
    }
}

bool game_matrix::is_success()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            if (number_matrix[x][y] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

bool game_matrix::is_failure()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            if (number_matrix[x][y] == 0)
            {
                return false;
            }
            if (y + 1 < MATRIX_LARGE && number_matrix[x][y] == number_matrix[x][y + 1])
            {
                return false;
            }
            if (x + 1 < MATRIX_LARGE && number_matrix[x][y] == number_matrix[x + 1][y])
            {
                return false;
            }
        }
    }
    return true;
}
