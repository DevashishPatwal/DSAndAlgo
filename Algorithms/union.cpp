#include <iostream>
#include <set>
#include <vector>
using namespace std;

//O(n+m)
vector<int> unionWithSet(const vector<int> &n, const vector<int> &m);

int main()
{
    vector<int> n = {4, 6, 1, 2, 4, 8, 4};
    vector<int> m = {3, 1, 7, 8, 2, 6};
    sizeof(int);
    vector<int> r = unionWithSet(n, m);
    for (auto element : r)
    {
        cout << element << ",";
    }
    return 0;
}
vector<int> unionWithoutAuxilarySpace(const vector<int> &n, const vector<int> &m)
{
}
vector<int> unionWithSet(const vector<int> &n, const vector<int> &m)
{
    vector<int> result;
    set<int> s;
    for (auto a : n)
    {
        s.insert(a);
    }
    for (auto a : m)
    {
        s.insert(a);
    }
    for (auto a : s)
    {
        result.push_back(a);
    }
    return result;
}