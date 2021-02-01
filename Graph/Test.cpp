#include "Alg.h"

#include <iostream>

using namespace std;

void BFS_test()
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

void DFS_test()
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

void Kruskal_test()
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

    cout << "Kruskal:" << endl;
    Kruskal(gr);
}

void Prim_test()
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

    cout << "Prim:" << endl;
    Prim(gr);
}

void BellmanFord_Test()
{
    Graph gr;
    const VertexNumber s = 1, t = 2, x = 3, y = 4, z = 5;
    gr.addVertex(s, { {t,6}, {y,7} });
    gr.addVertex(t, { {x,5}, {y,8}, {z,-4} });
    gr.addVertex(x, { {t,-2} });
    gr.addVertex(y, { {x,-3},{z,9} });
    gr.addVertex(z, { {s,2}, {x,7 } });

    cout << "BellmanFord:" << endl;
    BellmanFord(gr,s);
}

void Dijkstra_test()
{
    Graph gr;
    const VertexNumber s = 1, t = 2, x = 3, y = 4, z = 5;
    gr.addVertex(s, { {t,10}, {y,5} });
    gr.addVertex(t, { {x,1}, {y,2} });
    gr.addVertex(x, { {z,4} });
    gr.addVertex(y, { {t,3},{z,2}, {x,9} });
    gr.addVertex(z, { {s,7}, {x,6} });

    cout << "Dijkstra:" << endl;
    Dijkstra(gr, s);
}

void PairsAsMatrixMultiplication_Test()
{
    Graph gr;
    gr.addVertex(1, { {2,3}, {3,8}, {5, -4} });
    gr.addVertex(2, { {5,7}, {4,1} });
    gr.addVertex(3, { {2,4} });
    gr.addVertex(4, { {1,2},{3,-5} });
    gr.addVertex(5, { {4,6} });
    PairsAsMatrixMultiplication(gr);
}

int main()
{
    BFS_test(); cout << endl << endl;
    DFS_test(); cout << endl << endl;
    Kruskal_test(); cout << endl << endl;
    Prim_test(); cout << endl << endl;
    BellmanFord_Test(); cout << endl << endl;
    Dijkstra_test(); cout << endl << endl;
    PairsAsMatrixMultiplication_Test(); cout << endl << endl;
}
