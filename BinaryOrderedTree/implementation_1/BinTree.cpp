#ifndef __BINTREECPP
#define __BINTREECPP

#include "BinTree.h"

template <class T>
BinTree<T>::BinTree(Node* rt): root(rt) {}

template <class T>
BinTree<T>::BinTree(const BinTree<T>& tree): root(nullptr)
{
    root = clone(tree.root);
}

template <class T>
BinTree<T>& BinTree<T>::operator=(const BinTree<T>& tree)
{
    if (this != &tree)
    {
        clear(root);
        root = clone(tree.root);
    }
    return *this;
}

template <class T>
bool BinTree<T>::add(const T& data)
{
    if (root == nullptr)
    {
        root = new Node{data, nullptr, nullptr};
        return true;
    }

    Node** pNodePtr = &root;
    while (*pNodePtr != nullptr)
    {
        if ((*pNodePtr)->key == data)
            return false;
        else if ((*pNodePtr)->key > data)
            pNodePtr = &(*pNodePtr)->left;
        else
            pNodePtr = &(*pNodePtr)->right;
    }
    *pNodePtr = new Node{data, nullptr, nullptr};
    return true;
}

template <class T>
typename BinTree<T>::Node *BinTree<T>::search(const T& data)
{
    Node *crr = root;
    while (crr != nullptr && crr->key != data)
    {
        if (crr->key > data)
            crr = crr->left;
        else
            crr = crr->right;
    }
    return crr;
}

template <class T>
bool BinTree<T>::remove(const T& data)
{
    Node **target = &root;

    while (*target != nullptr && (*target)->key != data)
    {
        if ((*target)->key > data)
            target = &(*target)->left;
        else    
            target = &(*target)->right;
    }

    if (*target == nullptr)
        return false;

    Node *toDelete;
    if ((*target)->right == nullptr)
    {
        toDelete = *target;
        (*target) = (*target)->left;
    }
    else
    {
        Node **leftmost = &(*target)->right;

        while ((*leftmost)->left != nullptr)
        {
            leftmost = &(*leftmost)->left;    
        }
        (*target)->key = (*leftmost)->key;
        toDelete = *leftmost;
        *leftmost = (*leftmost)->right;
    }
    delete toDelete;
    return true;
}

template <class T>
void BinTree<T>::clear(Node *node)
{
    if (node != nullptr)
    {
        clear(node->left);
        clear(node->right);
        delete node;
        node->left = nullptr;
        node->right = nullptr;
    }
}

template <class T>
typename BinTree<T>::Node* BinTree<T>::clone(Node *node)
{
    if (node == nullptr)
        return nullptr; 

    return new Node{node->key, clone(node->left), clone(node->right)};
}


template <class T>
void BinTree<T>::print(Node* node) const
{
    if (node == nullptr)
        return;
    
    print(node->left);
    std::cout << node->key << ' ';
    print(node->right);
}

template <class T>
void BinTree<T>::print() const
{
    print(root);
    std::cout << '\n';
}

template <class T>
bool BinTree<T>::empty() const
{
    return root == nullptr;
}


template <class T>
BinTree<T>::~BinTree()
{
    clear(root);
}

template <class T>
BinTree<T>::Iterator::Iterator(const std::stack<Node *> &st, T l): s(st), last(l) {}

template <class T>
typename BinTree<T>::Iterator& BinTree<T>::Iterator::operator++()
{
    Node *crr = s.top();
    if (crr->left == nullptr)
    {
        last = crr->key;
        s.pop();
        if (crr->right != nullptr)
            s.push(crr->right);
    }
    else
    {
        last = crr->key;
        s.pop();
        if (crr->right != nullptr)
        {
            Node *leftmost = crr->right;
            while (leftmost != nullptr)
            {
                s.push(leftmost);
                leftmost = leftmost->left;        
            }
        }
    }

    return *this;
}

template <class T>
bool BinTree<T>::Iterator::operator!=(const Iterator& it) const
{
    if (it.s.empty() && s.empty())
        return false;
    return (s.empty() != it.s.empty()) || (s.top() != it.s.top() && last != it.last);
}

template <class T>
T& BinTree<T>::Iterator::operator*()
{
    return s.top()->key;
}

template <class T>
T BinTree<T>::Iterator::operator*() const
{
    return s.top()->key;
}

template <class T>
typename BinTree<T>::Iterator BinTree<T>::begin()
{
    if (root == nullptr)
        return end();

    std::stack<Node*> s;
    Node *crr = root;
    while (crr != nullptr)
    {
        s.push(crr);
        crr = crr->left; 
    }
    return Iterator(s, s.top()->key);
    
}

template <class T>
typename BinTree<T>::Iterator BinTree<T>::end()
{
    return Iterator();
}


template <class K>
std::ostream& operator<<(std::ostream& os, BinTree<K> &t)
{
    for (K el: t)
    {
        os << el << ' ';
    }
    return os;
}


#endif