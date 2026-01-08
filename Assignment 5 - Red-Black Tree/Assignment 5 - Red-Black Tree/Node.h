#ifndef NODE_H
#define NODE_H

class Node {
    friend class RedBlackTree;

private:
    int value;
    bool isBlack;
    bool isLeftChild;

    Node* parent;
    Node* left;
    Node* right;

public:
    Node(int val = 0)
        : value(val),
        isBlack(false),
        isLeftChild(false),
        parent(nullptr),
        left(nullptr),
        right(nullptr) {
    }
};

#endif
