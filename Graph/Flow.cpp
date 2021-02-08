#include "Alg.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

struct PathVertex
{
    int color = WHITE;
    unsigned int distance = 0;
    VertexNumber parent = NIL_VERTEX;

    enum { WHITE = 0, GRAY = 1, BLACK = 2 };

};

using Path = std::vector<PathVertex>;

void PrintPath(const Path& path)
{
    const PathVertex& pv = path.back();
    std::cout << path.size() - 1 << ' ';
    VertexNumber v = pv.parent;
    while (v != NIL_VERTEX)
    {
        std::cout << v << ' ';
        v = path[v].parent;
    }
    std::cout << std::endl;
}

void BFS(const Graph& graph, VertexNumber source, Path& path)
{
    path.clear();

    path.resize(graph.adjListSet.size());
    path[source].color = PathVertex::GRAY;
    path[source].distance = 0;

    std::queue<VertexNumber> visitQueue;
    visitQueue.push(source);

    while (!visitQueue.empty())
    {
        VertexNumber currentVertex = visitQueue.front();
        visitQueue.pop();

        const Graph::AdjList& ls = graph.adjListSet[currentVertex];
        for (auto adjVertex : ls)
        {
            if (adjVertex.weight == 0)
            {
                continue;
                //in this case we consider that edge is not exist
            }
            if (path[adjVertex.number].color == PathVertex::WHITE)
            {
                path[adjVertex.number].distance = path[currentVertex].distance;
                path[adjVertex.number].color = PathVertex::GRAY;
                path[adjVertex.number].distance++;
                path[adjVertex.number].parent = currentVertex;
                visitQueue.push(adjVertex.number);
            }
        }

        path[currentVertex].color = PathVertex::BLACK;
    }
}

Graph CreateResidualNetwork(const Graph& gr)
{
    //For every edge of the graph we add one inversed edge
    Graph residual;
    residual.adjListSet.resize(gr.adjListSet.size());

    for (VertexNumber source = 0; source < gr.adjListSet.size(); source++)
    {
        for (size_t dest = 0; dest < gr.adjListSet.size(); dest++)
        {
            const Graph::AdjList& adjList = gr.adjListSet[dest];
            for (const Graph::Vertex& v : adjList)
            {
                if (v.number == source)
                {
                    Graph::Vertex newVertex(dest, 0); //initial flow for inversed edge is 0
                    residual.adjListSet[source].push_back(newVertex);
                }
            }
        }
    }

    //Add edges of initial graph
    for (VertexNumber vertexNum = 0; vertexNum < gr.adjListSet.size(); vertexNum++)
    {
        const Graph::AdjList& ls = gr.adjListSet[vertexNum];
        for (const Graph::Vertex& adjVertex : ls)
        {
            residual.addVertex(vertexNum, { {adjVertex.number, adjVertex.weight} });
        }
    }
    return residual;
}

Weight GetMinCapacity(const Graph& graph, const Path& path, const VertexNumber source, const VertexNumber sink)
{
    VertexNumber v = sink; 

    const PathVertex& p = path.at(v);
    VertexNumber u = p.parent;
    Weight capacity = WEIGHT_NOT_DEFINED;

    while (u != NIL_VERTEX)
    {
        if (capacity > graph.getWeight(u, v))
        {
            capacity = graph.getWeight(u,v);
        }
        v = u;
        const PathVertex& p = path.at(v);
        u = p.parent;
    }

    if (v != source)
    {
        capacity = WEIGHT_NOT_DEFINED;
    }

    return capacity;
}

void EdmondsKarp(Graph& graph, VertexNumber source, VertexNumber sink)
{
    Graph residual = CreateResidualNetwork(graph);

    struct FlowAttribute
    {
        FlowAttribute(bool s = false, Weight f = 0) : flow(f), straight(s) {}
        Weight flow;
        bool straight; //direction (straight or inversed)
    };

    using Attributes = Matrix<FlowAttribute>;
    Attributes attributes(residual.getVertexCount(), residual.getVertexCount());

    graph.forEachEadge(
        [&attributes](VertexNumber source, VertexNumber dest, Weight weight)
        {
            attributes[source - 1][dest - 1].straight = true;
            return true;
        }
    );

    Path path;
    BFS(residual, source, path);
    Weight cmin = GetMinCapacity(residual, path, source, sink);

    while (cmin != WEIGHT_NOT_DEFINED)
    {
        VertexNumber v = sink;

        while (path[v].parent != NIL_VERTEX)
        {
            VertexNumber u = path[v].parent;
            Weight capacity = graph.getWeight(u, v); //It might be better to to keep it in the Attrtibute
            if (attributes[u-1][v-1].straight)
            {
                attributes[u - 1][v - 1].flow += cmin;
                residual.setWeight(u, v, capacity - attributes[u - 1][v - 1].flow);
                residual.setWeight(v, u, attributes[u - 1][v - 1].flow);

            }
            else
            {
                attributes[u - 1][v - 1].flow -= cmin;
                residual.setWeight(u, v, attributes[u - 1][v - 1].flow);
                residual.setWeight(v, u, capacity - attributes[u - 1][v - 1].flow);
            }
            v = u;
        }

        BFS(residual, source, path);
        cmin = GetMinCapacity(residual, path, source, sink);
    }

    const Graph::AdjList& ls = residual.adjListSet[sink];

    Weight maxFlow = 0;
    for (const Graph::Vertex& v : ls)
    {
        maxFlow += v.weight;
    }

    std::cout << "max flow is " << maxFlow;
}