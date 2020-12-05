#ifndef __BTREE
#define __BTREE
#include <iostream>
#include <stack>

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

    template <class K>
    friend std::ostream& operator<<(std::ostream& os, BinTree<K> &t);

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

    class Iterator
    {
    private:
        std::stack<Node *> s;
        T last;
    public:
        Iterator() = default;
        Iterator(const std::stack<Node *> &st, T l);
        ~Iterator() = default;
        Iterator& operator++();
        T& operator*();
        T operator*() const;
        bool operator!=(const Iterator& it) const;
    };

    Iterator begin();
    Iterator end();
};


#include "BinTree.cpp"

#endif