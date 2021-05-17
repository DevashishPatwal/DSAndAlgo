#include <iostream>
#include <set>
#include <vector>
using namespace std;

//O(n+m)
vector<int> intersection(const vector<int> &n, const vector<int> &m);

int main()
{
    vector<int> n = {4, 6, 1, 2, 4, 8, 4};
    vector<int> m = {3, 1, 7, 8, 2, 6};
    sizeof(int);
    vector<int> i = intersection(n, m);
    for (auto i : i)
    {
        cout << i << ",";
    }

    return 0;
}

vector<int> intersection(const vector<int> &n, const vector<int> &m)
{
    vector<int> result;
    set<int> s;
    for (auto a : n)
    {
        s.insert(a);
    }
    set<int>::iterator itr;
    for (auto a : m)
    {

        itr = s.find(a);
        if (itr != s.end())
        {
            result.push_back(a);
        }
    }
    return result;
}