#include "Alg.h"

#include <iostream>

using namespace std;

void BFS_Test()
{
    Graph g;
    g.addVertex(1, { 2,3 });
    g.addVertex(2, { 4,5,3 });
    g.addVertex(3, { 1,2,5,8,7 });
    g.addVertex(4, { 2,5 });
    g.addVertex(5, { 2,4,6 });
    g.addVertex(6, { 5 });
    g.addVertex(7, { 3, 8 });
    g.addVertex(8, { 3,7 });
    g.addVertex(9, { 10 });
    g.addVertex(10, { 9 });
    g.addVertex(11, { 12 });
    g.addVertex(12, { 11,13 });
    g.addVertex(13, { 12 });

    cout << "BFS " << "1:" << endl;
    BFS(g, 1);
}

void DFS_Test()
{
    Graph g;
    g.addVertex(1, { 2,3 });
    g.addVertex(2, { 4,5,3 });
    g.addVertex(3, { 1,2,5,8,7 });
    g.addVertex(4, { 2,5 });
    g.addVertex(5, { 2,4,6 });
    g.addVertex(6, { 5 });
    g.addVertex(7, { 3, 8 });
    g.addVertex(8, { 3,7 });
    g.addVertex(9, { 10 });
    g.addVertex(10, { 9 });
    g.addVertex(11, { 12 });
    g.addVertex(12, { 11,13 });
    g.addVertex(13, { 12 });
    cout << "DFS:" << endl;
    DFS(g);
}

void Kruskal_Test()
{
    Graph gr;
    const VertexNumber a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8, i = 9;
    gr.addVertex(a, { {b,4},{h,8} });
    gr.addVertex(b, { {a,4},{c,8},{h,11} });
    gr.addVertex(c, { {b,8},{i,2},{d,7},{f,4} });
    gr.addVertex(d, { {c,7},{e,9},{f,14} });
    gr.addVertex(e, { {d,9},{f,10} });
    gr.addVertex(f, { {g,2},{c,4},{d,14},{e,10} });
    gr.addVertex(g, { {h,1},{i,6},{f,2} });
    gr.addVertex(h, { {a,8},{b,11}, {i,7}, {g,1} });
    gr.addVertex(i, { {h,7},{c,2},{g,6}, {b,15} });

    cout << "Kruskal" << endl;
    Kruskal(gr);
}

int main()
{
    BFS_Test();
    cout << endl << endl;
    DFS_Test();
    cout << endl << endl;
    Kruskal_Test();
    cout << endl << endl;
}
