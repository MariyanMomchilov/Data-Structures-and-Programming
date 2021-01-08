#include "Graph.h"
#include <fstream>
#include <queue>
#include <stack>

Graph::Graph(size_t _size): size(_size)
{
    nodes.resize(size);
    createKeys();
}

void Graph::createKeys()
{
    for (size_t i = 0; i < size; i++)
    {
        nodes[i] = new Node{i, 0};
    }
}

void Graph::clear()
{
    for (size_t i = 0; i < size; i++)
    {
        delete nodes[i];
    }
}

void Graph::copyNeighbours(const Graph &g)
{
    for (size_t i = 0; i < g.size; i++)
    {
        for (size_t j = 0; j < g.nodes[i]->neighbours.size(); j++)
        {
            nodes[i]->neighbours.push_back(nodes[g.nodes[i]->neighbours[j]->key]);
        }
    }
}


bool Graph::addEdge(size_t from, size_t to)
{
    for (auto i = 0; i < nodes[from]->neighbours.size(); i++)
    {
        if (nodes[from]->neighbours[i] == nodes[to])
            return false;
    }

    nodes[from]->neighbours.push_back(nodes[to]);
    addEdge(to, from);
    return true;
}

bool Graph::removeEdge(size_t from, size_t to)
{
    size_t verticesSize = nodes[from]->neighbours.size(); 
    for (auto i = 0; verticesSize; i++)
    {
        if (nodes[from]->neighbours[i] == nodes[to])
        {
            nodes[from]->neighbours[i] = nodes[from]->neighbours[verticesSize - 1];
            nodes[from]->neighbours.pop_back();
            removeEdge(to, from);
            return true;
        }
    }
    return false;
}

Graph::Graph(const Graph &g): size(g.size)
{
    nodes.resize(size);
    createKeys();
    copyNeighbours(g);
}

Graph& Graph::operator=(const Graph &g)
{
    if (this != &g)
    {
        clear();
        size = g.size;
        createKeys();
        copyNeighbours(g);
    }
    return *this;
}

void Graph::setWeight(size_t node, int w)
{
    nodes[node]->weight = w;
}


Graph::~Graph()
{
    clear();
}


void Graph::bfsDot(std::ofstream &f, size_t startFrom) const
{
    f << "digraph {\n";

    bool *added = new bool[size]{false};
    std::queue<size_t> q;
    q.push(nodes[startFrom]->key);
    added[startFrom] = true;

    Node *crr;

    while (!q.empty())
    {
        crr = nodes[q.front()];
        q.pop();

        f << '\t' << crr->key << ";\n";

        for (size_t i = 0; i < crr->neighbours.size(); i++)
        {
            if (!added[crr->neighbours[i]->key])
            {
                added[crr->neighbours[i]->key] = true;
                q.push(crr->neighbours[i]->key);

                f << '\t' << crr->key << "->" << crr->neighbours[i]->key << ";\n";
            }
        }
    }
    f << "\n}";

    delete[] added;
}


void Graph::dfsDot(std::ofstream &f, size_t startFrom) const
{
    bool *added = new bool[size]{false};
    added[startFrom] = true;

    std::stack<size_t> s;
    s.push(nodes[startFrom]->key);

    f << "digraph {\n";


    Node *crr;
    bool toPop = false;
    while (!s.empty())
    {
        crr = nodes[s.top()];
        f << '\t' << crr->key << ";\n";

        for (size_t i = 0; i < crr->neighbours.size(); i++)
        {
            toPop = true;
            if (!added[crr->neighbours[i]->key])
            {
                added[crr->neighbours[i]->key] = true;
                s.push(crr->neighbours[i]->key);
                toPop = false;

                f << '\t' << crr->key << "->" << crr->neighbours[i]->key << ";\n";

                break;
            }
        }

        if (toPop)
            s.pop();
    }

    f << "\n}";

    delete[] added;
}