#include <iostream>
#include <math.h>
using namespace std;
int countRecursion(int n)
{
    int i = INT32_MAX, j = INT32_MAX;
    if (n <= 1)
    {
        return 0;
    }
    i = countRecursion(n - 1);
    cout << "Square root of " << n << " is " << sqrt(n) << endl;
    j = countRecursion(n - sqrt(n));

    return 1 + min(i, j);
}

int main()
{
    cout << countRecursion(4);

    return 0;
}