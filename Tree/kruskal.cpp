/*Program to find minning spanning tree*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Edge
{
public:
    int source;
    int destination;
    int weight;

    Edge(int source, int destination, int weight)
    {
        this->source = source;
        this->destination = destination;
        this->weight = weight;
    }
    friend bool compareEdgeWeight(Edge, Edge);
};
int parent(int child, int *ptr)
{
    while (ptr[child] != child)
    {
        child = ptr[child];
    }
    return child;
}
bool compareEdgeWeight(Edge e1, Edge e2)
{
    return (e1.weight < e2.weight);
}
vector<Edge> kruskal(vector<Edge> edgeList, int vertices)
{
    vector<Edge> spanningTree;
    int *array = new int[vertices];
    int count = 0, i = 0;
    for (int i = 0; i < vertices; i++)
    {
        array[i] = i;
    }
    sort(edgeList.begin(), edgeList.end(), compareEdgeWeight);

    while (count != vertices - 1)
    {
        Edge edge = edgeList[i++];
        int sourceParent = parent(edge.source, array);
        int destParent = parent(edge.destination, array);
        if (sourceParent != destParent)
        {
            array[sourceParent] = destParent;
            spanningTree.push_back(edge);
            count += 1;
        }
    }
    return spanningTree;
}

int main()
{
    std::vector<Edge> edgesList;
    edgesList.push_back(Edge(0, 1, 4));
    edgesList.push_back(Edge(0, 3, 1));
    edgesList.push_back(Edge(0, 2, 5));
    edgesList.push_back(Edge(3, 4, 10));
    edgesList.push_back(Edge(3, 2, 8));
    edgesList.push_back(Edge(1, 6, 11));
    edgesList.push_back(Edge(1, 5, 6));
    edgesList.push_back(Edge(1, 2, 2));
    edgesList.push_back(Edge(2, 6, 3));
    edgesList.push_back(Edge(7, 8, 7));
    edgesList.push_back(Edge(6, 8, 10));
    edgesList.push_back(Edge(5, 8, 5));
    edgesList.push_back(Edge(5, 6, 12));
    edgesList.push_back(Edge(5, 7, 13));
    vector<Edge> mst = kruskal(edgesList, 9);
    int minimumCost = 0;
    for (Edge e : mst)
    {
        minimumCost += e.weight;
        cout << "Src : " << e.source << " Dest : " << e.destination << " Weight : " << e.weight << endl;
    }
    cout << minimumCost;
}