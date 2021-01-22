#pragma once

#include <list>
#include <vector>

using VertexNumber = size_t;
using VertexWeight = int;

class Graph
{
public:
    struct Vertex
    {
        Vertex(VertexNumber n, VertexWeight w = 0) : number(n), weight(w) {}

        VertexNumber number;
        VertexWeight weight;
    };
    using AdjList = std::list<Vertex>;
    using AdjListSet = std::vector< AdjList>;

    AdjListSet adjListSet;

    using VertexNumberWeight = std::pair< VertexNumber, VertexWeight>;

    void addVertex(VertexNumber number, std::initializer_list<VertexNumber> adjVertices);
    void addVertex(VertexNumber number, std::initializer_list<VertexNumberWeight> adjVertices);
};
