#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> countingSort(vector<int> &n)
{
    vector<int> result;
    int max = n[0];
    int min = n[0];
    map<int, int> m;
    cout << INT32_MAX << endl;
    cout << m.max_size() << endl;
    //fill the map
    for (auto element : n)
    {
        if (max < element)
        {
            max = element;
        }
        else if (min > element)
        {
            min = element;
        }
        m[element] = m[element] += 1;
    }

    //map iterator used  for method find()
    map<int, int>::iterator it;

    //fill the vector result with sorted values
    for (int i = min; i <= max; i++)
    {
        it = m.find(i);
        if (it != m.end())
        {
            for (int j = 0; j < m.at(i); j++)
            {
                result.push_back(i);
            }
        }
    }

    return result;
}
int main()
{

    vector<int> n = {-1, -4, 3, 3, 2, 1, 4, 72, 12, 13, 45, 15, 16, -4, 16, 2, 8, 5, 1000, 1};
    vector<int> result = countingSort(n);
    for (auto e : result)
    {
        cout << e << ", ";
    }
    return 0;
}