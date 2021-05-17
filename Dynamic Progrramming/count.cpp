#include <iostream>
using namespace std;

int countMemoization(int n, int *p)
{
    int i = INT32_MAX, j = INT32_MAX;
    if (n == 1)
    {
        return 0;
    }
    if (p[n - 1] == INT32_MAX)
        p[n - 1] = countMemoization(n - 1, p);

    if (n % 3 == 0)
    {
        i = p[n / 3];
    }
    else if (n % 2 == 0)
    {
        j = p[n / 2];
    }
    p[n] = 1 + min(p[n - 1], min(i, j));

    return p[n];
}
int countMemoization(int n)
{
    int *p = new int[n + 1];
    for (int i = 0; i <= n; i++)
    {
        p[i] = INT32_MAX;
    }

    return countMemoization(n, p);
}
int countRecursion(int n)
{
    int i = INT32_MAX, j = INT32_MAX, k = INT32_MAX;
    if (n == 1)
    {
        return 0;
    }
    i = countRecursion(n - 1);
    if (n % 3 == 0)
    {
        j = countRecursion(n / 3);
    }
    if (n % 2 == 0)
    {
        k = countRecursion(n / 2);
    }

    return 1 + min(i, min(j, k));
}
int countDP(int n)
{
    int arr[n + 1];
    arr[1] = 0;
    arr[2] = 1;
    arr[3] = 1;
    if (n > 3)
    {
        for (int i = 4; i <= n; i++)
        {
            if (i % 3 == 0)
            {
                arr[i] = arr[i / 3] + 1;
            }
            else if (i % 2 == 0)
            {
                if (arr[i - 1] < arr[i / 2])
                {
                    arr[i] = arr[i - 1] + 1;
                }
                else
                {

                    arr[i] = arr[i / 2] + 1;
                }
            }
            else
            {

                arr[i] = arr[i - 1] + 1;
            }
        }
    }
    return arr[n];
}
int main()
{
    for (int i = 1; i <= 1000; i++)
    {
        cout << i << " = " << countDP(i) << " , ";
        cout << countRecursion(i) << endl;
    }
    // cout << countRecursion();
    return 0;
}