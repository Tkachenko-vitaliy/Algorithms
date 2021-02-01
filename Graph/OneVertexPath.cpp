#include "Alg.h"
#include "PriorityQueue.h"

#include <vector>
#include <iostream>
#include <queue>
#include <assert.h>

using namespace std;

void BellmanFord(Graph& graph, VertexNumber source)
{
    struct Attribute
    {
        Attribute(VertexNumber number) : node(number), parent(NIL_VERTEX), distance(WEIGHT_NOT_DEFINED) {}
        VertexNumber node;
        VertexNumber parent;
        Weight distance;
    };

    vector<Attribute> attributes;

    for (size_t i = 0; i < graph.adjListSet.size(); i++)
    {
        attributes.emplace_back(Attribute(i));
    }

    attributes[source].distance = 0;

    auto IterateEdges = [&attributes](VertexNumber first, VertexNumber second, Weight weight)
    {
        //Relax procedure
        if (attributes[first].distance != WEIGHT_NOT_DEFINED)
        {
            Weight newDistance = attributes[first].distance + weight;
            if (attributes[second].distance > newDistance)
            {
                attributes[second].distance = newDistance;
                attributes[second].parent = first;
            }
        }

        return true;
    };
 
    for (size_t iterNumber  = 1; iterNumber <= graph.getVertexCount()-1; iterNumber++)
    {
        graph.forEachEadge(IterateEdges);
    }
    

    bool isCycleNegativeWeight = false;

    auto DetectCycles = [&attributes, &isCycleNegativeWeight](VertexNumber first, VertexNumber second, Weight weight)
    {
        if (attributes[second].distance > attributes[first].distance + weight)
        {
            isCycleNegativeWeight = true;
            return false;
        }
        else
        {
            return true;
        }
    };

    graph.forEachEadge(DetectCycles);

    if (isCycleNegativeWeight)
    {
        cout << "Negative cycle is detected" << endl;
    }
    else
    {
        for (Attribute& attr : attributes)
        {
            if (attr.node == NIL_VERTEX)
                continue;

            cout << attr.node << ": " << "(" << attr.distance << ") ";
            
            VertexNumber parent = attr.parent;
            while (parent != NIL_VERTEX)
            {
                cout << parent << '-';
                parent = attributes[parent].parent;
            }

            cout << endl;
        }
    }
 }

void Dijkstra(Graph& graph, VertexNumber source)
{
    struct Attribute
    {
        Attribute(VertexNumber number): node(number), parent(NIL_VERTEX), distance(WEIGHT_NOT_DEFINED) {}
        bool operator< (const Attribute& attr) const { return distance < attr.distance; }

        VertexNumber node;
        VertexNumber parent;
        Weight distance;
    };
    
    using AttributeQueue = PriorityQueue<Attribute>;
    AttributeQueue queue;
    vector<Attribute> output;
    
    for (size_t vertex = 1; vertex <= graph.getVertexCount(); vertex++) //Nill vertex is ignored
    {
        Attribute attr(vertex);
        if (source == vertex)
            attr.distance = 0;
        queue.push(attr);
    }

    output.push_back(Attribute(NIL_VERTEX)); //To facilitate a search of parent vertex

    while (!queue.empty())
    {
        Attribute current = queue.pop();
        output.push_back(current);
        Graph::AdjList& ls = graph.adjListSet[current.node];
        for (Graph::Vertex& adjNode : ls)
        {
            //Relax procedure
            AttributeQueue::iterator adjNodeAttribute = find_if(queue.begin(), queue.end(), [&adjNode](const Attribute& attr) {return adjNode.number == attr.node; });
            if (adjNodeAttribute != queue.end()) //Node has not been visited yet
            {
                Weight newDistance = current.distance + adjNode.weight;
                if (adjNodeAttribute->distance > newDistance)
                {
                    adjNodeAttribute->distance = newDistance;
                    adjNodeAttribute->parent = current.node;
                    queue.decrease_priority(adjNodeAttribute);
                }
            }
        }
    }

    sort(output.begin(), output.end(), [](const Attribute& first, const Attribute& second) {return first.node < second.node; });

    for (Attribute& attr : output)
    {
        if (attr.node == NIL_VERTEX)
            continue;

        cout << attr.node << ": " << "(" << attr.distance << ") ";

        VertexNumber parent = attr.parent;
        while (parent != NIL_VERTEX)
        {
            cout << parent << '-';
            parent = output[parent].parent;
        }

        cout << endl;
    }
}