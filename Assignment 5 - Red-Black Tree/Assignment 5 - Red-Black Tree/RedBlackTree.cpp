#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() : root(nullptr) {}

RedBlackTree::~RedBlackTree() {
    destroy(root);
}

void RedBlackTree::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

RedBlackTree::RedBlackTree(const RedBlackTree& other) {
    root = copyTree(other.root, nullptr);
}

Node* RedBlackTree::copyTree(Node* node, Node* parent) {
    if (!node) return nullptr;
    Node* newNode = new Node(node->value);
    newNode->isBlack = node->isBlack;
    newNode->parent = parent;
    newNode->left = copyTree(node->left, newNode);
    newNode->right = copyTree(node->right, newNode);
    return newNode;
}

RedBlackTree& RedBlackTree::operator=(const RedBlackTree& other) {
    if (this != &other) {
        destroy(root);
        root = copyTree(other.root, nullptr);
    }
    return *this;
}

// ---------- INSERT ----------
void RedBlackTree::insert(int value) {
    Node* newNode = new Node(value);
    Node* parent = nullptr;
    Node* curr = root;

    while (curr) {
        parent = curr;
        if (value < curr->value)
            curr = curr->left;
        else
            curr = curr->right;
    }

    newNode->parent = parent;
    if (!parent)
        root = newNode;
    else if (value < parent->value) {
        parent->left = newNode;
        newNode->isLeftChild = true;
    }
    else {
        parent->right = newNode;
        newNode->isLeftChild = false;
    }

    fixInsert(newNode);
}

void RedBlackTree::remove(int value) {
    Node* z = root;
    while (z && z->value != value)
        z = (value < z->value) ? z->left : z->right;

    if (!z) return;

    Node* y = z;
    Node* x;
    bool yOriginalBlack = y->isBlack;

    if (!z->left) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (!z->right) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        yOriginalBlack = y->isBlack;
        x = y->right;

        if (y->parent == z) {
            if (x) x->parent = y;
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->isBlack = z->isBlack;
    }

    delete z;

    if (yOriginalBlack && x)
        fixDelete(x);
}


void RedBlackTree::rotateLeft(Node*& x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x->isLeftChild)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
    x->isLeftChild = true;
}

void RedBlackTree::rotateRight(Node*& x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (!x->isLeftChild)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
    x->isLeftChild = false;
}

void RedBlackTree::fixInsert(Node*& node) {
    while (node != root && !node->parent->isBlack) {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        if (parent->isLeftChild) {
            Node* uncle = grandparent->right;
            if (uncle && !uncle->isBlack) {
                parent->isBlack = true;
                uncle->isBlack = true;
                grandparent->isBlack = false;
                node = grandparent;
            }
            else {
                if (!node->isLeftChild) {
                    node = parent;
                    rotateLeft(node);
                }
                parent->isBlack = true;
                grandparent->isBlack = false;
                rotateRight(grandparent);
            }
        }
        else {
            Node* uncle = grandparent->left;
            if (uncle && !uncle->isBlack) {
                parent->isBlack = true;
                uncle->isBlack = true;
                grandparent->isBlack = false;
                node = grandparent;
            }
            else {
                if (node->isLeftChild) {
                    node = parent;
                    rotateRight(node);
                }
                parent->isBlack = true;
                grandparent->isBlack = false;
                rotateLeft(grandparent);
            }
        }
    }
    root->isBlack = true;
}

void RedBlackTree::fixDelete(Node*& x) {
    while (x != root && (!x || x->isBlack)) {
        Node* sibling;

        if (x == x->parent->left) {
            sibling = x->parent->right;

            if (!sibling->isBlack) {
                sibling->isBlack = true;
                x->parent->isBlack = false;
                rotateLeft(x->parent);
                sibling = x->parent->right;
            }

            if ((!sibling->left || sibling->left->isBlack) &&
                (!sibling->right || sibling->right->isBlack)) {
                sibling->isBlack = false;
                x = x->parent;
            }
            else {
                if (!sibling->right || sibling->right->isBlack) {
                    if (sibling->left)
                        sibling->left->isBlack = true;
                    sibling->isBlack = false;
                    rotateRight(sibling);
                    sibling = x->parent->right;
                }

                sibling->isBlack = x->parent->isBlack;
                x->parent->isBlack = true;
                if (sibling->right)
                    sibling->right->isBlack = true;
                rotateLeft(x->parent);
                x = root;
            }
        }
        else {
            sibling = x->parent->left;

            if (!sibling->isBlack) {
                sibling->isBlack = true;
                x->parent->isBlack = false;
                rotateRight(x->parent);
                sibling = x->parent->left;
            }

            if ((!sibling->left || sibling->left->isBlack) &&
                (!sibling->right || sibling->right->isBlack)) {
                sibling->isBlack = false;
                x = x->parent;
            }
            else {
                if (!sibling->left || sibling->left->isBlack) {
                    if (sibling->right)
                        sibling->right->isBlack = true;
                    sibling->isBlack = false;
                    rotateLeft(sibling);
                    sibling = x->parent->left;
                }

                sibling->isBlack = x->parent->isBlack;
                x->parent->isBlack = true;
                if (sibling->left)
                    sibling->left->isBlack = true;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    if (x) x->isBlack = true;
}

void RedBlackTree::transplant(Node* u, Node* v) {
    if (!u->parent)
        root = v;
    else if (u->isLeftChild)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v)
        v->parent = u->parent;
}

Node* RedBlackTree::minimum(Node* node) {
    while (node->left)
        node = node->left;
    return node;
}

// ---------- SEARCH ----------
bool RedBlackTree::searchIterative(int value) const {
    Node* curr = root;
    while (curr) {
        if (value == curr->value) return true;
        curr = (value < curr->value) ? curr->left : curr->right;
    }
    return false;
}

Node* RedBlackTree::searchRecursive(Node* node, int value) const {
    if (!node || node->value == value) return node;
    if (value < node->value)
        return searchRecursive(node->left, value);
    return searchRecursive(node->right, value);
}

bool RedBlackTree::searchRecursive(int value) const {
    return searchRecursive(root, value) != nullptr;
}

// ---------- TRAVERSALS ----------
void RedBlackTree::preorder(Node* node) const {
    if (!node) return;
    cout << node->value << " ";
    preorder(node->left);
    preorder(node->right);
}

void RedBlackTree::inorder(Node* node) const {
    if (!node) return;
    inorder(node->left);
    cout << node->value << " ";
    inorder(node->right);
}

void RedBlackTree::postorder(Node* node) const {
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->value << " ";
}

void RedBlackTree::printPreorder() const {
    preorder(root);
    cout << endl;
}

void RedBlackTree::printInorder() const {
    inorder(root);
    cout << endl;
}

void RedBlackTree::printPostorder() const {
    postorder(root);
    cout << endl;
}
