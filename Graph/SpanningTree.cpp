#include "Alg.h"
#include "PriorityQueue.h"

#include <set>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

struct Edge
{
    Edge(VertexNumber first = 0, VertexNumber second = 0, Weight weight = 0) : first(first), second(second), weight(weight) {}

    VertexNumber first;
    VertexNumber second;
    Weight weight;
};

void Kruskal(Graph& graph)
{
    using DisjointSet = list<set<VertexNumber>>;
    DisjointSet disjointSet;

    for (size_t vnum = 0; vnum < graph.adjListSet.size(); vnum++)
    {
        disjointSet.emplace_back(set<VertexNumber>({ vnum }));
    }

    vector<Edge> edges;

    for (VertexNumber vertexSource = 0; vertexSource < graph.adjListSet.size(); vertexSource++)
    {
        Graph::AdjList& adjList = graph.adjListSet[vertexSource];
        for (Graph::Vertex& secondVertex : adjList)
        {
            edges.push_back(Edge(vertexSource, secondVertex.number, secondVertex.weight));
        }
    }

    sort(edges.begin(), edges.end(),
        [](const Edge& first, const Edge& second) {return first.weight < second.weight; }
    );

    vector<Edge> includedEdges;

    for (Edge& edge : edges)
    {
        DisjointSet::iterator firstEadgeSetIt = disjointSet.end(), secondEadgeSetIt = disjointSet.end();
        for (DisjointSet::iterator currentIterator = disjointSet.begin(); currentIterator!=disjointSet.end(); currentIterator++)
        {
            if (firstEadgeSetIt == disjointSet.end())
            {
                set<VertexNumber>& setVertex = (*currentIterator);
                auto findIt = setVertex.find(edge.first);
                if (findIt != setVertex.end())
                {
                    firstEadgeSetIt = currentIterator;
                }
            }

            if (secondEadgeSetIt == disjointSet.end())
            {
                set<VertexNumber>& setVertex = (*currentIterator);
                auto findIt = setVertex.find(edge.second);
                if (findIt != setVertex.end())
                {
                    secondEadgeSetIt = currentIterator;
                }
            }

            if (firstEadgeSetIt != disjointSet.end() && secondEadgeSetIt != disjointSet.end()) //both vertices are found
            {
                if (firstEadgeSetIt != secondEadgeSetIt) //Vertices are in different set
                {
                    includedEdges.push_back(edge);
                    (*secondEadgeSetIt).insert((*firstEadgeSetIt).begin(), (*firstEadgeSetIt).end());
                    disjointSet.erase(firstEadgeSetIt);
                    break;
                }
            }
        }
    }

    for (auto& edge: includedEdges)
    {
        cout << edge.first << '-' << edge.second << ' ' << edge.weight << endl;
    }
}

void Prim(Graph& graph)
{
    struct Node
    {
        Node(VertexNumber num = NIL_VERTEX, VertexNumber prnt = NIL_VERTEX, Weight weight = WEIGHT_NOT_DEFINED) :
            number(num), parent(prnt), key(weight) {}
        VertexNumber number;
        VertexNumber parent;
        Weight key;

        bool operator < (const Node& n) const { return key < n.key; }
    };

    using NodeQueue = PriorityQueue<Node>;

    NodeQueue nodeQueue;

    vector<Node> output;

    for (VertexNumber num = 1; num < graph.adjListSet.size(); num++) //number 0 is nil
    {
        nodeQueue.push(Node(num));
    }

    nodeQueue.back().key = 0;

    while (!nodeQueue.empty())
    {
        Node currentNode = nodeQueue.pop();
        
        Graph::AdjList& adjList = graph.adjListSet[currentNode.number];
        for (Graph::Vertex& adjNode : adjList)
        {
            auto adjInQueue = find_if(nodeQueue.begin(), nodeQueue.end(),
                [&adjNode](const Node& n) { return adjNode.number == n.number; }
            );

            if (adjInQueue != nodeQueue.end()) //The adjacent node is in queue
            {
                if (adjNode.weight < adjInQueue->key)
                {
                    adjInQueue->key = adjNode.weight;
                    adjInQueue->parent = currentNode.number;
                    nodeQueue.decrease_priority(adjInQueue);
                }
            }
        }

        if (currentNode.parent != NIL_VERTEX)
            output.push_back(currentNode);
    }

    for (Node& n: output)
    {
        cout << n.number  << '-' << n.parent << ' ' << n.key << endl;
    }
}

