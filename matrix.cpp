#include "matrix.h"

int Matrix::getNumber(int x, int y)
{
    return numberMatrix[x][y];
}

void Matrix::initMatrix()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            numberMatrix[x][y] = 0;
        }
    }
}

void Matrix::addNumber()
{
    vector<Point> availableList;

    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            if (numberMatrix[x][y] == 0)
            {
                availableList.push_back({ x, y });
            }
        }
    }
    if (!availableList.empty())
    {
        int randIndex = rand() % availableList.size();
        int randX = availableList[randIndex].x;
        int randY = availableList[randIndex].y;

        numberMatrix[randX][randY] = 2;
    }
}

void Matrix::moveUp()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 1; y < MATRIX_LARGE; y++)
        {
            for (int i = y; i > 0 && numberMatrix[x][i] != 0; i--)
            {
                if (numberMatrix[x][i - 1] == 0)
                {
                    numberMatrix[x][i - 1] = numberMatrix[x][i];
                    numberMatrix[x][i] = 0;
                }
                else if (numberMatrix[x][i] == numberMatrix[x][i - 1])
                {
                    numberMatrix[x][i - 1] *= 2;
                    numberMatrix[x][i] = 0;
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
            for (int i = y; i < MATRIX_LARGE - 1 && numberMatrix[x][i] != 0; i++)
            {
                if (numberMatrix[x][i + 1] == 0)
                {
                    numberMatrix[x][i + 1] = numberMatrix[x][i];
                    numberMatrix[x][i] = 0;
                }
                else if (numberMatrix[x][i] == numberMatrix[x][i + 1])
                {
                    numberMatrix[x][i + 1] *= 2;
                    numberMatrix[x][i] = 0;
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
            for (int i = x; i > 0 && numberMatrix[i][y] != 0; i--)
            {
                if (numberMatrix[i - 1][y] == 0)
                {
                    numberMatrix[i - 1][y] = numberMatrix[i][y];
                    numberMatrix[i][y] = 0;
                }
                else if (numberMatrix[i][y] == numberMatrix[i - 1][y])
                {
                    numberMatrix[i - 1][y] *= 2;
                    numberMatrix[i][y] = 0;
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
            for (int i = x; i < MATRIX_LARGE - 1 && numberMatrix[i][y] != 0; i++)
            {
                if (numberMatrix[i + 1][y] == 0)
                {
                    numberMatrix[i + 1][y] = numberMatrix[i][y];
                    numberMatrix[i][y] = 0;
                }
                else if (numberMatrix[i][y] == numberMatrix[i + 1][y])
                {
                    numberMatrix[i + 1][y] *= 2;
                    numberMatrix[i][y] = 0;
                }
                else { break; }
            }
        }
    }
}

bool Matrix::isSuccess()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            if (numberMatrix[x][y] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

bool Matrix::isFailure()
{
    for (int x = 0; x < MATRIX_LARGE; x++)
    {
        for (int y = 0; y < MATRIX_LARGE; y++)
        {
            if (numberMatrix[x][y] == 0)
            {
                return false;
            }
            if (y + 1 < MATRIX_LARGE && numberMatrix[x][y] == numberMatrix[x][y + 1]) { return false; }
            if (x + 1 < MATRIX_LARGE && numberMatrix[x][y] == numberMatrix[x + 1][y]) { return false; }
        }
    }
    return true;
}