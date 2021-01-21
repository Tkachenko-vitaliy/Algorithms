#include "Alg.h"

#include <queue>
#include <iostream>

using namespace std;

const int NO_DESTINATION = std::numeric_limits<int>::max();

struct Attribute
{
    int color;
    int distance;
    int parent;
    int open;
    int close;

    enum { WHITE = 0, GRAY = 1, BLACK = 2 };

    Attribute()
    {
        color = WHITE;
        parent = 0;
        distance = NO_DESTINATION;
        int open = 0;
        int close = 0;
    }
};

using  AttributeList = std::vector<Attribute>;

void BFS(Graph& graph, NodeNumber source)
{
    AttributeList attrList;
    attrList.resize(graph.adjListSet.size());
    attrList[source].color = Attribute::GRAY;
    attrList[source].distance = 0;

    queue<int> visitQueue;
    visitQueue.push(source);

    while (!visitQueue.empty())
    {
        NodeNumber currentNode = visitQueue.front();
        visitQueue.pop();

        Graph::AdjList& ls = graph.adjListSet[currentNode];
        for (auto adjNode : ls)
        {
            if (attrList[adjNode].color == Attribute::WHITE)
            {
                attrList[adjNode].distance = attrList[currentNode].distance;
                attrList[adjNode].color = Attribute::GRAY;
                attrList[adjNode].distance++;
                attrList[adjNode].parent = currentNode;
                visitQueue.push(adjNode);
            }
        }

        attrList[currentNode].color = Attribute::BLACK;
        cout << currentNode << ' ';
    }

    cout << endl;
    for (size_t i = 0; i < attrList.size(); i++)
    {
        Attribute attrItem = attrList[i];
        if (attrItem.distance == NO_DESTINATION)
            cout << i << '-' << 'N' << ' ';
        else
            cout << i << '-' << attrItem.distance << ' ';
    }
}

void DFS(Graph& graph, AttributeList& attrList, NodeNumber currentNode, int& time)
{
    cout << currentNode << ' ';

    time++;
    attrList[currentNode].open = time;
    attrList[currentNode].color = Attribute::GRAY;

    Graph::AdjList& al = graph.adjListSet[currentNode];
    for (NodeNumber adjNode : al)
    {
        if (attrList[adjNode].color == Attribute::WHITE)
        {
            attrList[adjNode].parent = currentNode;
            DFS(graph,attrList, adjNode, time);
        }
    }
    time++;
    attrList[currentNode].close = time;
    attrList[currentNode].color = Attribute::BLACK;
}

void DFS(Graph& graph)
{
    AttributeList attrList;
    attrList.resize(graph.adjListSet.size());

    int time = 0;
    for (size_t i = 0; i < graph.adjListSet.size(); i++)
    {
        if (attrList[i].color == Attribute::WHITE)
        {
            DFS(graph, attrList, i, time);
        }
    }

    cout << endl;
    for (size_t i = 0; i < attrList.size(); i++)
    {
        Attribute attrItem = attrList[i];
        cout << i << '[' << attrItem.open << '-' << attrItem.close << ']' << ' ';
    }
}