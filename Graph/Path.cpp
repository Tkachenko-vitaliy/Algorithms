#include "Alg.h"

#include <vector>
#include <iostream>
#include <queue>

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

