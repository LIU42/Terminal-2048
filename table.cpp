#include "table.h"

int tables::get_data(int x, int y)
{
    return data[x][y];
}

void tables::init_data()
{
    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 0; y < TABLE_LARGE; y++)
        {
            data[x][y] = 0;
        }
    }
}

void tables::add_number(int count = 1)
{
    static point add_list[BLOCK_COUNT];
    static int add_list_length;

    for (int i = 0; i < count; i++)
    {
        for (int x = 0; x < TABLE_LARGE; x++)
        {
            for (int y = 0; y < TABLE_LARGE; y++)
            {
                if (data[x][y] == 0)
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

            data[rand_x][rand_y] = 2;
            add_list_length = 0;
        }
    }
}

void tables::up_action()
{
    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 1; y < TABLE_LARGE; y++)
        {
            while (y > 0 && data[x][y] != 0)
            {
                if (data[x][y - 1] == 0)
                {
                    data[x][y - 1] = data[x][y];
                    data[x][y] = 0;
                    y -= 1;
                }
                else if (data[x][y] == data[x][y - 1])
                {
                    data[x][y - 1] *= 2;
                    data[x][y] = 0;
                    y -= 1;
                }
                else { break; }
            }
        }
    }
    add_number();
}

void tables::down_action()
{
    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = TABLE_LARGE - 2; y >= 0; y--)
        {
            while (y < TABLE_LARGE - 1 && data[x][y] != 0)
            {
                if (data[x][y + 1] == 0)
                {
                    data[x][y + 1] = data[x][y];
                   data[x][y] = 0;
                    y += 1;
                }
                else if (data[x][y] == data[x][y + 1])
                {
                    data[x][y + 1] *= 2;
                    data[x][y] = 0;
                    y += 1;
                }
                else { break; }
            }
        }
    }
    add_number();
}

void tables::left_action()
{
    for (int y = 0; y < TABLE_LARGE; y++)
    {
        for (int x = 1; x < TABLE_LARGE; x++)
        {
            while (x > 0 && data[x][y] != 0)
            {
                if (data[x - 1][y] == 0)
                {
                    data[x - 1][y] = data[x][y];
                    data[x][y] = 0;
                    x -= 1;
                }
                else if (data[x][y] == data[x - 1][y])
                {
                    data[x - 1][y] *= 2;
                    data[x][y] = 0;
                    x -= 1;
                }
                else { break; }
            }
        }
    }
    add_number();
}

void tables::right_action()
{
    for (int y = 0; y < TABLE_LARGE; y++)
    {
        for (int x = TABLE_LARGE - 2; x >= 0; x--)
        {
            while (x < TABLE_LARGE - 1 && data[x][y] != 0)
            {
                if (data[x + 1][y] == 0)
                {
                    data[x + 1][y] = data[x][y];
                    data[x][y] = 0;
                    x += 1;
                }
                else if (data[x][y] == data[x + 1][y])
                {
                    data[x + 1][y] *= 2;
                    data[x][y] = 0;
                    x += 1;
                }
                else { break; }
            }
        }
    }
    add_number();
}

bool tables::is_win()
{
    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 0; y < TABLE_LARGE; y++)
        {
            if (data[x][y] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

bool tables::is_lose()
{
    for (int x = 0; x < TABLE_LARGE; x++)
    {
        for (int y = 0; y < TABLE_LARGE; y++)
        {
            if (data[x][y] != 0)
            {
                if (y > 0 && data[x][y] == data[x][y - 1]) { return false; }
                if (x > 0 && data[x][y] == data[x - 1][y]) { return false; }
                if (y < TABLE_LARGE - 1 && data[x][y] == data[x][y + 1]) { return false; }
                if (x < TABLE_LARGE - 1 && data[x][y] == data[x + 1][y]) { return false; }
            }
            else { return false; }
        }
    }
    return true;
}