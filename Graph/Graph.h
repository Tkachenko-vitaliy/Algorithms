#pragma once

#include <list>
#include "Matrix.h"

#include <vector>
#include <functional>

using VertexNumber = size_t;
using Weight = int;

const VertexNumber NIL_VERTEX = 0; //we concider 0 as non-exist vertex 
const Weight WEIGHT_NOT_DEFINED = std::numeric_limits<Weight>::max();

using AdjacencyMatrix = Matrix<Weight>;

class Graph
{
public:
    Graph();
    Graph(const Graph& gr);
    Graph(Graph&& gr);

    struct Vertex
    {
        Vertex(VertexNumber n, Weight w = 0) : number(n), weight(w) {}

        VertexNumber number;
        Weight weight;
    };
    using AdjList = std::list<Vertex>;
    using AdjListSet = std::vector< AdjList>;

    //Nill vertex will be presented as the first item in array
    AdjListSet adjListSet;

    using VertexNumberWeight = std::pair< VertexNumber, Weight>;

    void addVertex(VertexNumber number, std::initializer_list<VertexNumber> adjVertices);
    void addVertex(VertexNumber number, std::initializer_list<VertexNumberWeight> adjVertices);
    size_t getVertexCount() const; //a count without nill vertex
    void forEachEadge(std::function<bool(VertexNumber source, VertexNumber dest, Weight weight)>) const;
    Graph getTransposedDirection() const; //return graph with transponsed direction: all incoming vertex are turned into outgoing
    AdjacencyMatrix getAdjacencyMatrix() const;

    Graph& operator = (const Graph& copy) { adjListSet = copy.adjListSet; return *this;  }
    Graph& operator = (Graph&& copy) { adjListSet = std::move(copy.adjListSet); return *this; }
};
