#ifndef __BINTREECPP
#define __BINTREECPP
#include "BinTree.h"
#include <stdexcept>

template <class T>
BinTree<T>::BinTree(): root(nullptr) {}

template <class T>
void BinTree<T>::insert(const T &data)
{
    if (root == nullptr)
        root = new Node{data, nullptr, nullptr, nullptr};
    else
    {   
        Node *p = nullptr;
        Node *crr = root;
        while (crr != nullptr)
        {
            p = crr;

            if (crr->key > data)
                crr = crr->left;
            else if (crr->key < data)
                crr = crr->right;
            else
                throw std::overflow_error("Key already in the tree\n");
        }
        if (p->key > data)
            p->left = new Node{data, p, nullptr, nullptr};
        else
            p->right = new Node{data, p, nullptr, nullptr};
    }
}

template <class T>
typename BinTree<T>::Node *BinTree<T>::search(const T &data)
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
void BinTree<T>::erase(const T &data)
{
    Node *trashed = search(data);
    if (trashed == nullptr)
        return;
    else
    {
        Node *tmp;

        // case 1
        if (trashed->right == nullptr)
        {
            if (trashed == root)
            {
                if (root->left != nullptr)
                    root->left->parent = nullptr;
                root = root->left;

            }
            else
            {
                trashed->parent->left = trashed->left;
                if (trashed->left != nullptr)
                    trashed->left->parent = trashed->parent;
            }
            delete trashed;
        }
        // case 2
        else
        {
            // find smallest subtree in trashed->right
            Node *smallest = trashed->right;
            while (smallest->left != nullptr)
                smallest = smallest->left;

            trashed->key = smallest->key;
            if (trashed->right == smallest)
                smallest->parent->right = smallest->right;
            else        
                smallest->parent->left = smallest->right;
            smallest->right->parent = smallest->parent;
            delete smallest;
        }
    }
    
}
template <class T>
bool BinTree<T>::in(const T &data) const
{
    return nullptr != search(data);
}
template <class T>
inline bool BinTree<T>::empty() const
{
    return root == nullptr;
}

template <class T>
void BinTree<T>::clear(Node *node)
{
    if (node != nullptr)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <class T>
BinTree<T>::~BinTree()
{
    clear(root);
}


#endif