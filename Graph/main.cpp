#include "Graph.h"
#include <fstream>

int main()
{
    Graph g(8);

    g.addEdge(7, 4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 4);
    g.addEdge(1, 5);
    g.addEdge(1, 4);
    g.addEdge(1, 7);
    g.addEdge(5, 4);

    std::ofstream bfs("bfs.dot");
    std::ofstream dfs("dfs.dot");

    g.bfsDot(bfs, 0);
    bfs.close();
    g.dfsDot(dfs, 0);
    dfs.close();

}