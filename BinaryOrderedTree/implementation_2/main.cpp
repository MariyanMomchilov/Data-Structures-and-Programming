#include <iostream>
#include "BinTree.h"

int main()
{
    BinTree<int> tree;
    tree.insert(30);
    tree.insert(10);
    tree.insert(100);
    tree.insert(5);
    tree.insert(80);
    tree.insert(200);
    tree.insert(90);
    tree.insert(95);
    tree.insert(97);

    tree.erase(30);

    BinTree<int> tree2;
    tree2.insert(30);
    tree2.erase(30);

    BinTree<int> tree3;
    tree3.insert(30);
    tree3.insert(105);
    tree3.insert(106);
    tree3.insert(107);
    tree3.erase(105);

    return 0;
}