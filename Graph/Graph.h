#ifndef __GRAPH_H
#define __GRAPH_H
#include <iostream>
#include <vector>


class Graph
{
    struct Node
    {
        size_t key;
        int weight;
        std::vector<Node*> neighbours;
    };

    void createKeys();
    void copyNeighbours(const Graph &g);
    void clear();
    
public:
    Graph(size_t _size = 0);
    Graph(const Graph &g);
    Graph& operator=(const Graph &g);
    
    bool addEdge(size_t from, size_t to);
    bool removeEdge(size_t from, size_t to);
    void setWeight(size_t node, int w);
    void bfsDot(std::ofstream &f, size_t startFrom) const;
    void dfsDot(std::ofstream &f, size_t startFrom) const;
    ~Graph();

private:
    size_t size;
    std::vector<Node*> nodes;
};

#endif