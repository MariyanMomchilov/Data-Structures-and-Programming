#ifndef __BINTREE
#define __BINTREE

template <class T>
class BinTree
{
private:
    struct Node
    {
        T key;
        Node *parent;
        Node *left, *right;
    };

    Node *root;

    Node *search(const T &data);
    void clear(Node *node);
public:
    BinTree();
    void insert(const T &data);
    void erase(const T &data);
    bool in(const T &data) const;
    inline bool empty() const;
    ~BinTree();
};

#include "BinTree.cpp"

#endif