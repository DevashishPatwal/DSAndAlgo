#include <bits/stdc++.h>
using namespace std;
int possibleTrees(int h, int x, int y, int i)
{
    if (i == h)
    {
        return x;
    }
    int m = pow(10, 9) + 7;
    long res1 = (long)x * x;
    long res2 = (long)x * y * 2;
    int ans1 = (int)(res1 % m);
    int ans2 = (int)(res2 % m);
    int value = (ans1 + ans2) % m;
    return possibleTrees(h, value, x, i + 1);
}
int possibleTrees(int height)
{
    if (height < 2)
    {
        return 1;
    }
    return possibleTrees(height, 1, 1, 1);
}
int main()
{
    int height;
    cout << "Enter the height : ";
    cin >> height;
    cout << possibleTrees(height);
    return 0;
}