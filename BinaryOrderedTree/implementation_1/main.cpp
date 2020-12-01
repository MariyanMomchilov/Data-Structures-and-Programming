#include "BinTree.h"

int main()
{
    BinTree<int> tree;
    tree.add(10);

    tree.add(5);
    tree.add(2);
    tree.add(20);
    tree.add(17);
    tree.add(18);
    tree.add(19);
    tree.add(30);

    tree.remove(10);
    tree.print();
    std::cout << '\n';

    tree.remove(5);
    tree.print();
    std::cout << '\n';

    tree.remove(18);
    tree.print();
    std::cout << '\n';
}