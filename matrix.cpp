#include "matrix.h"

int Matrix::getNumber(int x, int y)
{
    return numbers[x][y];
}

void Matrix::initNumbers()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            numbers[x][y] = 0;
        }
    }
}

void Matrix::addNumber()
{
    Point availableList[BLOCK_COUNT];
    int availableListLength = 0;

    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            if (numbers[x][y] == 0)
            {
                availableList[availableListLength].x = x;
                availableList[availableListLength].y = y;
                availableListLength += 1;
            }
        }
    }
    if (availableListLength != 0)
    {
        int randIndex = rand() % availableListLength;
        int randX = availableList[randIndex].x;
        int randY = availableList[randIndex].y;

        numbers[randX][randY] = 2;
    }
}

void Matrix::moveUp()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 1; y < MATRIX_LARGE; y++)
        {
            for (int i = y; i > 0 && numbers[x][i] != 0; i--)
            {
                if (numbers[x][i - 1] == 0)
                {
                    numbers[x][i - 1] = numbers[x][i];
                    numbers[x][i] = 0;
                }
                else if (numbers[x][i] == numbers[x][i - 1])
                {
                    numbers[x][i - 1] *= 2;
                    numbers[x][i] = 0;
                }
                else { break; }
            }
        }
    }
}

void Matrix::moveDown()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = MATRIX_LARGE - 2; y >= 0; y--)
        {
            for (int i = y; i < MATRIX_LARGE - 1 && numbers[x][i] != 0; i++)
            {
                if (numbers[x][i + 1] == 0)
                {
                    numbers[x][i + 1] = numbers[x][i];
                    numbers[x][i] = 0;
                }
                else if (numbers[x][i] == numbers[x][i + 1])
                {
                    numbers[x][i + 1] *= 2;
                    numbers[x][i] = 0;
                }
                else { break; }
            }
        }
    }
}

void Matrix::moveLeft()
{
    for (int y = 0; y < MATRIX_LARGE; y++)
    {
        for (int x = 1; x < MATRIX_LARGE; x++)
        {
            for (int i = x; i > 0 && numbers[i][y] != 0; i--)
            {
                if (numbers[i - 1][y] == 0)
                {
                    numbers[i - 1][y] = numbers[i][y];
                    numbers[i][y] = 0;
                }
                else if (numbers[i][y] == numbers[i - 1][y])
                {
                    numbers[i - 1][y] *= 2;
                    numbers[i][y] = 0;
                }
                else { break; }
            }
        }
    }
}

void Matrix::moveRight()
{
    for (int y = 0; y < MATRIX_LARGE; y++)
    {
        for (int x = MATRIX_LARGE - 2; x >= 0; x--)
        {
            for (int i = x; i < MATRIX_LARGE - 1 && numbers[i][y] != 0; i++)
            {
                if (numbers[i + 1][y] == 0)
                {
                    numbers[i + 1][y] = numbers[i][y];
                    numbers[i][y] = 0;
                }
                else if (numbers[i][y] == numbers[i + 1][y])
                {
                    numbers[i + 1][y] *= 2;
                    numbers[i][y] = 0;
                }
                else { break; }
            }
        }
    }
}

bool Matrix::isWin()
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

bool Matrix::isLose()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            if (numbers[x][y] == 0)
            {
                return false;
            }
            if (y + 1 < MATRIX_LARGE && numbers[x][y] == numbers[x][y + 1]) { return false; }
            if (x + 1 < MATRIX_LARGE && numbers[x][y] == numbers[x + 1][y]) { return false; }
        }
    }
    return true;
}