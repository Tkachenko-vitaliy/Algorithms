#pragma once

#include "Graph.h"

void BFS(Graph& graph, VertexNumber source);
void DFS(Graph& graph);
void Kruskal(Graph& graph);
void Prim(Graph& graph);
void BellmanFord(Graph& graph, VertexNumber source);
void Dijkstra(Graph& graph, VertexNumber source);
void PairsAsMatrixMultiplication(Graph& graph);
void FloydWarshall(Graph& graph);
void EdmondsKarp(Graph& graph, VertexNumber source, VertexNumber sink);