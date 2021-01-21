#pragma once

#include <list>
#include <vector>

using NodeNumber = unsigned int;

class Graph
{
public:

    using AdjList = std::list<NodeNumber>;
    using AdjListSet = std::vector< AdjList>;

    AdjListSet adjListSet;

    void addNode(NodeNumber node, std::initializer_list<NodeNumber> adjNodes);
};
