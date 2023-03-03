#include <iostream>
#include "RBTree.h"
#include "order_set.hpp"

// void func(int* & a)
// {
//     std::cout << a[0];
// }

int main()
{
    RBTree<int>* tree = new RBTree<int>();
    std::cout << sizeof(*tree) << std::endl;
    // int a[9] = {163, 117, 47, 15, 98, 62, 133, 185, 76};
    int a[9] = {47, 117, 163, 15, 98, 62, 133, 185, 76};
    // int a[3] = {5,6,7};
    for(int i = 0; i < 9; i++)
    {
        tree->insert(a[i]);
        tree->preorder();
        std::cout << "\n";
    }
    std::cout << tree->minimum() << std::endl;
    std::cout << tree->maximum() << std::endl;
    tree->inorder();    
    std::cout << "\n";
    tree->remove(47);
    tree->inorder();

    std::cout << "\n";
    std::cout << "\t12\n";
    std::cout << "    12\n";
    std::cout << "        12\n";

    delete tree;
    std::cout<< '\n';
    int *b = new int[9]{5,6,7,1,2,2,5,6,7};
    order_set<int> root(b, 9);
    // std::cout << 5555 << std::endl;
    root.func()->inorder();
    delete[] b;

}