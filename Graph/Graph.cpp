// Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Graph.h"

void Graph::addNode(NodeNumber node, std::initializer_list<NodeNumber> adjNodes)
{
    if (node >= (NodeNumber)adjListSet.size())
        adjListSet.resize(node+1);
    adjListSet[node] = adjNodes;
}


