#include <iostream>
using namespace std;
#define size 4
void printMatrix(bool **matrix)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
bool safeToPlace(bool **matrix, int row, int col)
{
    int i, j;
    //above
    i = row;
    while (i >= 0)
    {
        if (matrix[i--][col] == true)
        {
            return false;
        }
    }
    i = col;
    //left
    while (i >= 0)
    {
        if (matrix[row][i--] == true)
        {
            return false;
        }
    }

    i = row;
    j = col;
    //left diagonal
    while (i >= 0 && j >= 0)
    {
        if (matrix[i--][j--] == true)
        {
            return false;
        }
    }
    i = row;
    j = col;
    //Right diagonal
    while (i >= 0 && j < size)
    {
        if (matrix[i--][j++] == true)
        {
            return false;
        }
    }

    return true;
}
//tq -> Total Queen
//qsf -> Queen so far
void NQueen(bool **matrix, int order, int row, int col, int qsf, int tq)
{
    if (qsf == tq)
    {
        printMatrix(matrix);
        return;
    }
    if (col >= order)
    {
        col = 0;
        row += 1;
    }
    if (row == order)
    {
        return;
    }
    if (safeToPlace(matrix, row, col))
    {
        matrix[row][col] = true;
        NQueen(matrix, size, row + 1, 0, qsf + 1, tq);
        matrix[row][col] = false;
    }
    NQueen(matrix, size, row, col + 1, qsf, tq);
}
int main()
{
    bool **matrix = new bool *[size] { nullptr };
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new bool[size]{0};
    }

    NQueen(matrix, size, 0, 0, 0, 4);

    //deallocate memory
    for (int i = 0; i < size; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}