// Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Graph.h"

Graph::Graph()
{

}

Graph::Graph(const Graph& gr)
{
    *this = gr;
}

Graph::Graph(Graph&& gr)
{
    *this = gr;
}

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

Graph Graph::getInversedDirection() const
{
    Graph retGraph;
    retGraph.adjListSet.resize(adjListSet.size());

    for (VertexNumber source = 0; source < adjListSet.size(); source++)
    {
        for (size_t dest = 0; dest < adjListSet.size(); dest++)
        {
            const AdjList& adjList = adjListSet[dest];
            for (const Vertex& v : adjList)
            {
                if (v.number == source)
                {
                    Vertex newVertex(dest, v.weight);
                    retGraph.adjListSet[source].push_back(newVertex);
                }
            }
        }
    }

    return retGraph;
}

AdjacencyMatrix Graph::getAdjacencyMatrix() const
{
    AdjacencyMatrix adjMatrix(getVertexCount(), getVertexCount());

    adjMatrix.fill(WEIGHT_NOT_DEFINED);

    for (size_t i = 0; i < getVertexCount(); i++)
    {
        adjMatrix.set(i, i, 0);
    }

    forEachEadge(
        [&adjMatrix](VertexNumber source, VertexNumber dest, Weight weight)
        {
            adjMatrix.set(source-1, dest-1, weight);
            return true;
        }
    );

    return adjMatrix;
}