#include <bits/stdc++.h>
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

bool canMove(bool **matrix, const vector<pair<int, int>> &visited, const pair<int, int> &cordinates)
{
    pair<int, int> pairToSearch;

    // check whether cordinates are out of bounds or not
    if (cordinates.first < 0 || cordinates.first >= size || cordinates.second < 0 || cordinates.second >= size)
    {
        return false;
    }

    // check if cordidnates have value 0 or not
    if (matrix[cordinates.first][cordinates.second] == 0)
    {
        return false;
    }

    //check if cordinates already visited or not;
    for (auto &&i : visited)
    {
        if (i == cordinates)
        {
            return false;
        }
    }

    return true;
}

void ratInAMaze(bool **matrix, int order, vector<pair<int, int>> &visited, const pair<int, int> start, const pair<int, int> end)
{
    visited.push_back(start);
    if (start == end)
    {

        for (auto &&i : visited)
        {
            cout << "(" << i.first << "," << i.second << ")"
                 << "->";
        }
        cout << "END" << endl;
        visited.pop_back();
        return;
    }

    pair<int, int> left = {start.first, start.second - 1};
    pair<int, int> right = {start.first, start.second + 1};
    pair<int, int> top = {start.first - 1, start.second};
    pair<int, int> bottom = {start.first + 1, start.second};

    if (canMove(matrix, visited, left))
    {
        ratInAMaze(matrix, order, visited, left, end);
    }
    if (canMove(matrix, visited, right))
    {
        ratInAMaze(matrix, order, visited, right, end);
    }
    if (canMove(matrix, visited, top))
    {
        ratInAMaze(matrix, order, visited, top, end);
    }
    if (canMove(matrix, visited, bottom))
    {
        ratInAMaze(matrix, order, visited, bottom, end);
    }
    visited.pop_back();
}
int main()
{
    bool **const matrix = new bool *[size] { nullptr };
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new bool[size];
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = 1;
        }
    }
    // matrix[0][3] = 0;
    // matrix[0][2] = 0;
    // matrix[0][1] = 0;
    // matrix[1][3] = 0;
    // matrix[1][2] = 0;
    // matrix[1][1] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 0;
    matrix[2][3] = 0;
    printMatrix(matrix);
    vector<pair<int, int>> visited;
    ratInAMaze(matrix, size, visited, {3, 3}, {3, 0});

    //deallocate memory
    for (int i = 0; i < size; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}