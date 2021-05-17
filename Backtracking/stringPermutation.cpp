#include <iostream>
using namespace std;
void permutations(string inputString, int start, int end)
{
    if (start == end)
    {
        cout << inputString << endl;
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            string str = inputString.at(i) + inputString.substr(0, i) + inputString.substr(i + 1, end);
            //recursion
            permutations(str, start + 1, end);
        }
    }
}

int main()
{
    string input = "abc";
    permutations(input, 0, input.length() - 1);
    return 0;
}