#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;
class Graph
{
    int **ptr;
    int n;
    void DFSHelper(int **p, int sv, bool *visited)
    {
        cout << sv;
        visited[sv] = true;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && p[sv][i])
            {
                DFSHelper(p, i, visited);
            }
        }
    }
    bool *allocateVisitedArray()
    {
        return new bool[n]{false};
    }
    bool isLoopPresentHelper(int **p, int sv, bool *visited, int parent)
    {
        visited[sv] = true;
        for (int i = 0; i < n; i++)
        {
            if (p[sv][i] && i != parent && visited[i])
            {
                return true;
            }
            else if (!visited[i] && p[sv][i])
            {
                return isLoopPresentHelper(p, i, visited, sv);
            }
        }
        return false;
    }
    void connectedComponenetsHelper(int **p, int sv, bool *visited, vector<int> &temp)
    {
        temp.push_back(sv);
        visited[sv] = true;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && p[sv][i])
            {
                connectedComponenetsHelper(p, i, visited, temp);
            }
        }
    }
    void isConnectedHelper(int **p, int sv, bool *visited)
    {
        visited[sv] = true;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && p[sv][i])
            {
                isConnectedHelper(p, i, visited);
            }
        }
    }
    void pathHelper(int **ptr, int from, int to, bool *visited)
    {
        if (from == to)
        {
            return;
        }
        visited[from] = true;
        for (int i = 0; i < n; i++)
        {
            if (ptr[from][i] == 1 && !visited[i])
            {
                pathHelper(ptr, i, to, visited);
            }
        }
    }

public:
    Graph(int n)
    {
        ptr = new int *[n];
        for (int i = 0; i < n; i++)
        {
            ptr[i] = new int[n]{0};
        }
        this->n = n;
    }
    void edge(int a, int b)
    {
        ptr[a][b] = 1;
        ptr[b][a] = 1;
    }

    vector<vector<int>> connectedComponenets()
    {
        bool *visited = new bool[n]{false};
        vector<vector<int>> vector;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                std::vector<int> temp;
                connectedComponenetsHelper(ptr, i, visited, temp);
                vector.push_back(temp);
            }
        }

        delete[] visited;
        return vector;
    }

    void DFS()
    {
        bool *visited = allocateVisitedArray();
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
                DFSHelper(ptr, i, visited);
        }
        cout << endl;
        delete[] visited;
    }
    bool isConnected()
    {
        bool *visited = allocateVisitedArray();
        isConnectedHelper(ptr, 0, visited);
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                delete[] visited;
                return false;
            }
        }
        delete[] visited;
        return true;
    }
    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << ptr[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    bool isLoopPresent()
    {
        bool *visited = allocateVisitedArray();
        return isLoopPresentHelper(ptr, 0, visited, 0);
    }
    void BFSHelper(int **ptr, bool *visited, queue<int> &nodesNotVisited)
    {
        if (nodesNotVisited.empty())
        {
            return;
        }
        int front = nodesNotVisited.front();
        cout << front;
        visited[front] = true;
        nodesNotVisited.pop();
        for (int i = 0; i < n; i++)
        {
            if (ptr[front][i] == 1 && !visited[i])
            {
                nodesNotVisited.push(i);
                visited[i] = true;
            }
        }
        BFSHelper(ptr, visited, nodesNotVisited);
    }
    // void shortestPathHelper(int **ptr, bool *visited, queue<int> &nodesNotVisited, int source, int destination, vector<int> &path)
    // {
    //     if (nodesNotVisited.empty())
    //     {
    //         return;
    //     }
    //     int front = nodesNotVisited.front();
    //     if (destination == source)
    //     {
    //         return path.push_back(source);
    //     }
    //     visited[front] = true;

    //     nodesNotVisited.pop();
    //     for (int i = 0; i < n; i++)
    //     {
    //         if (ptr[front][i] == 1 && !visited[i])
    //         {
    //             nodesNotVisited.push(i);
    //             visited[i] = true;
    //         }
    //     }
    //     shortestPathHelper(ptr, visited, nodesNotVisited, front, destination, path);
    //     path.push_back(front);
    // }
    // vector<int> shortestPath(int source, int destination)
    // {
    //     bool *visited = allocateVisitedArray();
    //     queue<int> nodesNotVisited;
    //     vector<int> path;
    //     nodesNotVisited.push(source);
    //     shortestPathHelper(ptr, visited, nodesNotVisited, source, destination, path);
    //     cout << path.size();
    // }

    void BFS()
    {
        bool *visited = allocateVisitedArray();
        queue<int> nodesNotVisited;
        nodesNotVisited.push(0);
        BFSHelper(ptr, visited, nodesNotVisited);
    }
    int lengthOfPath(int source, int destination)
    {
        if (source == destination)
        {
            return 0;
        }
        bool *visited = allocateVisitedArray();
        queue<pair<int, int>> nodesNotVisited;
        nodesNotVisited.push({source, 0});
        while (!nodesNotVisited.empty())
        {
            pair<int, int> p = nodesNotVisited.front();
            int front = p.first;
            if (destination == front)
            {
                return p.second;
            }
            visited[front] = true;
            nodesNotVisited.pop();

            for (int i = 0; i < n; i++)
            {
                if (ptr[front][i] == 1 && !visited[i])
                {
                    nodesNotVisited.push({i, p.second + 1});
                    visited[i] = true;
                }
            }
        }
        return -1;
    }

    bool hasPath(int from, int to)
    {
        bool *visited = allocateVisitedArray();
        return hasPathHelper(ptr, from, to, visited);
        delete[] visited;
    }
    bool hasPathHelper(int **ptr, int from, int to, bool *visited)
    {
        if (from == to)
        {
            return true;
        }
        visited[from] = true;
        for (int i = 0; i < n; i++)
        {
            if (ptr[from][i] == 1 && !visited[i])
            {
                return hasPathHelper(ptr, i, to, visited);
            }
        }
    }
    // if in a graph all vertices have even degree it has euler circuit
    bool hasEulerCircuit()
    {
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (ptr[i][j] == 1)
                {
                    count += 1;
                }
            }
            if (count % 2 != 0)
            {
                return false;
            }
        }
        return true;
    }
    // if in a graph has exactly two vertices having odd degree it has euler path
    bool hasEulerPath()
    {
        int degree = 0;
        int oddDegree = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (ptr[i][j] == 1)
                {
                    degree += 1;
                }
            }
            if (oddDegree >= 3)
            {
                return false;
            }
            else if (degree % 2 != 0)
            {
                oddDegree += 1;
            }
        }
        return oddDegree == 2 ? true : false;
    }
    void path(int from, int to)
    {
        bool *visited = allocateVisitedArray();
        pathHelper(ptr, from, to, visited);

        delete[] visited;
    }
};

int main()
{
    Graph n(6);
    n.edge(0, 1);
    n.edge(1, 2);
    n.edge(2, 5);
    n.edge(3, 1);
    n.edge(2, 4);
    n.edge(4, 3);
    cout << n.hasEulerCircuit();
    // n.print();
    // n.BFS();
    // cout << n.lengthOfPath(0, 5);
    // vector<vector<int>> test = n.connectedComponenets();

    // cout << '\n'
    //      << n.isConnected();
    // cout << '\n'
    //      << n.isLoopPresent();

    return 0;
}