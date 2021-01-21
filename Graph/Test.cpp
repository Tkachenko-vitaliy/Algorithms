#include "Alg.h"

#include <iostream>

using namespace std;

void BFS_Test()
{
    Graph g;
    g.addNode(1, { 2,3 });
    g.addNode(2, { 4,5,3 });
    g.addNode(3, { 1,2,5,8,7 });
    g.addNode(4, { 2,5 });
    g.addNode(5, { 2,4,6 });
    g.addNode(6, { 5 });
    g.addNode(7, { 3, 8 });
    g.addNode(8, { 3,7 });
    g.addNode(9, { 10 });
    g.addNode(10, { 9 });
    g.addNode(11, { 12 });
    g.addNode(12, { 11,13 });
    g.addNode(13, { 12 });

    cout << "BFS " << "1:" << endl;
    BFS(g, 1);
}

void DFS_Test()
{
    Graph g;
    g.addNode(1, { 2,3 });
    g.addNode(2, { 4,5,3 });
    g.addNode(3, { 1,2,5,8,7 });
    g.addNode(4, { 2,5 });
    g.addNode(5, { 2,4,6 });
    g.addNode(6, { 5 });
    g.addNode(7, { 3, 8 });
    g.addNode(8, { 3,7 });
    g.addNode(9, { 10 });
    g.addNode(10, { 9 });
    g.addNode(11, { 12 });
    g.addNode(12, { 11,13 });
    g.addNode(13, { 12 });
    cout << "DFS:" << endl;
    DFS(g);
}

int main()
{
    BFS_Test();
    cout << endl << endl;
    DFS_Test();
    cout << endl;
}
