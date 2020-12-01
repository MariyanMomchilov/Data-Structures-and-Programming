#ifndef __BTREE
#define __BTREE
#include <iostream>

template <class T>
class BinTree
{
private:
    struct Node
    {
        T key;
        Node *left, *right;
    };

    Node* root;


    void clear(Node *node);
    Node* clone(Node *node);
    void print(Node* node) const;

public:

    BinTree(Node* rt = nullptr);
    BinTree(const BinTree<T>& tree);
    BinTree<T>& operator=(const BinTree<T>& tree);
    ~BinTree();


    bool add(const T& data);
    Node *search(const T& data);
    bool remove(const T& data);
    bool empty() const;
    void print() const;
};


#include "BinTree.cpp"

#endif