#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "Node.h"
#include <iostream>
using namespace std;

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node*&);
    void rotateRight(Node*&);
    void fixInsert(Node*&);
    void fixDelete(Node*&);
    void transplant(Node*, Node*);
    Node* minimum(Node*);

    void preorder(Node*) const;
    void inorder(Node*) const;
    void postorder(Node*) const;

    Node* searchRecursive(Node*, int) const;
    void destroy(Node*);
    Node* copyTree(Node*, Node*);

public:
    RedBlackTree();
    RedBlackTree(const RedBlackTree&);
    ~RedBlackTree();

    RedBlackTree& operator=(const RedBlackTree&);

    void insert(int);
    void remove(int);

    bool searchIterative(int) const;
    bool searchRecursive(int) const;

    void printPreorder() const;
    void printInorder() const;
    void printPostorder() const;
};

#endif