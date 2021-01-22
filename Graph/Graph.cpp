// Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Graph.h"

void Graph::addVertex(VertexNumber number, std::initializer_list<VertexNumber> adjVertices)
{
    if (number >= adjListSet.size())
        adjListSet.resize(number +1);
    for (auto &item : adjVertices)
    {
        adjListSet[number].push_back(Vertex(item));
    }
}


void Graph::addVertex(VertexNumber number, std::initializer_list<VertexNumberWeight> adjVertices)
{
    if (number >= adjListSet.size())
        adjListSet.resize(number + 1);
    for (auto &item : adjVertices)
    {
        adjListSet[number].push_back(Vertex(item.first, item.second));
    }
}
