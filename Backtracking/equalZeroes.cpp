#include <iostream>
using namespace std;
void printMatrix(bool **matrix, int size)
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
bool safeToPlace(bool **matrix, int row, int col, int size)
{

    int count = 0;
    int safeCount = size / 2 - 1;
    for (int i = 0; i < size; ++i)
    {
        if (matrix[row][i])
        {
            count += 1;
        }
    }
    if (count > safeCount)
    {
        return false;
    }
    count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (matrix[i][col])
        {
            count += 1;
        }
    }
    if (count > safeCount)
    {
        return false;
    }
    return true;
}
void equalZeroes(bool **matrix, int row, int col, int size, int zeroplaced)
{
    if (zeroplaced == size * size / 2)
    {
        printMatrix(matrix, size);
        return;
    }
    if (col == size)
    {
        row += 1;
        col = 0;
    }
    if (row == size)
    {
        return;
    }

    if (safeToPlace(matrix, row, col, size))
    {
        matrix[row][col] = true;
        equalZeroes(matrix, row, col + 1, size, zeroplaced + 1);
        matrix[row][col] = false;
    }
    equalZeroes(matrix, row, col + 1, size, zeroplaced);
}
int main()
{
    int size = 4;
    bool **matrix = new bool *[size] { nullptr };
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new bool[size]{0};
    }
    equalZeroes(matrix, 0, 0, size, 0);
    //deallocate memory
    for (int i = 0; i < size; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}