#include "Alg.h"

#include <queue>
#include <iostream>

using namespace std;

const int NO_DESTINATION = std::numeric_limits<int>::max();

struct Attribute
{
    int color;
    int distance;
    VertexNumber parent;
    int open;
    int close;

    enum { WHITE = 0, GRAY = 1, BLACK = 2 };

    Attribute()
    {
        color = WHITE;
        parent = NIL_VERTEX;
        distance = NO_DESTINATION;
        int open = 0;
        int close = 0;
    }
};

using  AttributeList = std::vector<Attribute>;

void BFS(Graph& graph, VertexNumber source)
{
    AttributeList attrList;
    attrList.resize(graph.adjListSet.size());
    attrList[source].color = Attribute::GRAY;
    attrList[source].distance = 0;

    queue<VertexNumber> visitQueue;
    visitQueue.push(source);

    while (!visitQueue.empty())
    {
        VertexNumber currentVertex = visitQueue.front();
        visitQueue.pop();

        Graph::AdjList& ls = graph.adjListSet[currentVertex];
        for (auto adjVertex : ls)
        {
            if (attrList[adjVertex.number].color == Attribute::WHITE)
            {
                attrList[adjVertex.number].distance = attrList[currentVertex].distance;
                attrList[adjVertex.number].color = Attribute::GRAY;
                attrList[adjVertex.number].distance++;
                attrList[adjVertex.number].parent = currentVertex;
                visitQueue.push(adjVertex.number);
            }
        }

        attrList[currentVertex].color = Attribute::BLACK;
        cout << currentVertex << ' ';
    }

    cout << endl;
    for (size_t i = 0; i < attrList.size(); i++)
    {
        Attribute attrItem = attrList[i];
        if (attrItem.distance == 0)
            cout << i << '-' << 'N' << ' ';
        else
            cout << i << '-' << attrItem.distance << ' ';
    }
}

void DFS(Graph& graph, AttributeList& attrList, VertexNumber currentVertex, int& time)
{
    cout << currentVertex << ' ';

    time++;
    attrList[currentVertex].open = time;
    attrList[currentVertex].color = Attribute::GRAY;

    Graph::AdjList& al = graph.adjListSet[currentVertex];
    for (auto adjVertex : al)
    {
        if (attrList[adjVertex.number].color == Attribute::WHITE)
        {
            attrList[adjVertex.number].parent = currentVertex;
            DFS(graph,attrList, adjVertex.number, time);
        }
    }
    time++;
    attrList[currentVertex].close = time;
    attrList[currentVertex].color = Attribute::BLACK;
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