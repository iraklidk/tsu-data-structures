#include <iostream>
#include "RedBlackTree.h"

int main()
{
        RedBlackTree tree;

        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        tree.insert(15);
        tree.insert(5);

        cout << "Preorder: ";
        tree.printPreorder();

        cout << "Inorder: ";
        tree.printInorder();

        cout << "Postorder: ";
        tree.printPostorder();

        cout << "Search 15 (iter): " << (tree.searchIterative(15) ? "moidzebna" : "ver moidzebna") << endl;
        cout << "Search 15 (rec): " << (tree.searchRecursive(15) ? "moidzebna" : "ver moidzebna") << endl;
        cout << "Search 100 (iter): " << (tree.searchIterative(100) ? "moidzebna" : "ver moidzebna") << endl;
        cout << "Search 100 (rec): " << (tree.searchRecursive(100) ? "moidzebna" : "ver moidzebna") << endl;

        tree.remove(15);
        cout << "Search 15 (iter): " << (tree.searchIterative(15) ? "moidzebna" : "ver moidzebna") << endl;
        cout << "Search 15 (rec): " << (tree.searchRecursive(15) ? "moidzebna" : "ver moidzebna") << endl;

        RedBlackTree copyTree(tree);
        cout << "Copied tree preorder: ";
        copyTree.printPreorder();
}