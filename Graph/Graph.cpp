// Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

const int NO_DESTINATION = std::numeric_limits<int>::max();

class Graph
{
public:
    using NodeNumber = int;

    void addNode(NodeNumber node, std::initializer_list<int> adjNodes);
    void BFS(NodeNumber source);
    void DFS();
private:
    using AdjList = std::list<NodeNumber>;
    using AdjListSet = std::vector< AdjList>;
    AdjListSet adjListSet;

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

    void DFS(AttributeList& attrList, NodeNumber currentNode, int& time);
};

void Graph::addNode(NodeNumber node, std::initializer_list<int> adjNodes)
{
    if (node >= (int)adjListSet.size())
        adjListSet.resize(node+1);
    adjListSet[node] = adjNodes;
}

void Graph::BFS(NodeNumber source)
{
    AttributeList attrList;
    attrList.resize(adjListSet.size());
    attrList[source].color = Attribute::GRAY;
    attrList[source].distance = 0;

    std::queue<int> visitQueue;
    visitQueue.push(source);
    
    while (!visitQueue.empty())
    {
        NodeNumber currentNode = visitQueue.front();
        visitQueue.pop();

        AdjList& ls = adjListSet[currentNode];
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

void Graph::DFS(AttributeList& attrList, NodeNumber currentNode, int& time)
{
    cout << currentNode << ' ';

    time++;
    attrList[currentNode].open = time;
    attrList[currentNode].color = Attribute::GRAY;

    AdjList& al = adjListSet[currentNode];
    for (NodeNumber adjNode : al)
    {
        if (attrList[adjNode].color == Attribute::WHITE)
        {
            attrList[adjNode].parent = currentNode;
            DFS(attrList, adjNode, time);
        }
    }
    time++;
    attrList[currentNode].close = time;
    attrList[currentNode].color = Attribute::BLACK;
}

void Graph::DFS()
{
    AttributeList attrList;
    attrList.resize(adjListSet.size());

    int time = 0;
    for (size_t i = 0; i < adjListSet.size(); i++)
    {
        if (attrList[i].color == Attribute::WHITE)
        {
            DFS(attrList, i, time);
        }
    }

    cout << endl;
    for (size_t i = 0; i < attrList.size(); i++)
    {
        Attribute attrItem = attrList[i];
        cout << i << '[' << attrItem.open << '-' << attrItem.close << ']' << ' ';
    }
}

void BFS_Test()
{
    Graph g;
    g.addNode(1, { 2,3 });
    g.addNode(2, { 4,5,3 });
    g.addNode(3, { 1,2,5,8,7 });
    g.addNode(4, { 2,5 });
    g.addNode(5, { 2,4,6 });
    g.addNode(6, { 5 });
    g.addNode(7, { 3, 8 });
    g.addNode(8, { 3,7 });
    g.addNode(9, { 10 });
    g.addNode(10, { 9 });
    g.addNode(11, { 12 });
    g.addNode(12, { 11,13 });
    g.addNode(13, { 12 } );

    cout << "BFS " << "1:" << endl;
    g.BFS(1);
}

void DFS_Test()
{
    Graph g;
    g.addNode(1, { 2,3 });
    g.addNode(2, { 4,5,3 });
    g.addNode(3, { 1,2,5,8,7 });
    g.addNode(4, { 2,5 });
    g.addNode(5, { 2,4,6 });
    g.addNode(6, { 5 });
    g.addNode(7, { 3, 8 });
    g.addNode(8, { 3,7 });
    g.addNode(9, { 10 });
    g.addNode(10, { 9 });
    g.addNode(11, { 12 });
    g.addNode(12, { 11,13 });
    g.addNode(13, { 12 });
    cout << "DFS:" << endl;
    g.DFS();
}

int main()
{
    BFS_Test();
    cout << endl << endl;
    DFS_Test();
    cout << endl;
}
