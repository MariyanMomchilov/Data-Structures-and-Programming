#include "BinTree.h"

int main()
{
    BinTree<int> tree;
    std::cout << tree << '\n';
    
    tree.add(10);
    std::cout << tree << '\n';

    tree.add(5);
    tree.add(2);
    std::cout << tree << '\n';

    tree.add(20);
    tree.add(17);
    tree.add(18);
    tree.add(19);
    tree.add(30);

    tree.remove(10);
    tree.print();
    std::cout << tree << '\n';
    std::cout << '\n';

    tree.remove(5);
    tree.print();
    std::cout << tree << '\n';
    std::cout << '\n';

    tree.remove(18);
    tree.print();
    std::cout << tree << '\n';
}