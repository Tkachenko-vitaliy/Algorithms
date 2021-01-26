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

void Graph::forEachEadge(std::function<bool(VertexNumber source, VertexNumber dest, Weight weight)> fun) const
{
    for (size_t source = 1; source < adjListSet.size(); source++)
    {
        const AdjList& al = adjListSet[source];
        for (const Vertex &v : al)
        {
            bool res = fun(source, v.number, v.weight);
            if (res == false)
            {
                return;
            }
        }
    }
}

size_t Graph::getVertexCount() const 
{
    if (adjListSet.size() == 0)
    {
        return 0;
    }
    else
    {
        return adjListSet.size() - 1;
    }
}
