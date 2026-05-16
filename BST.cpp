#include "BST.h"
#include <algorithm>

BST::BST() {
    root = nullptr;
}

Node* BST::getRoot() {
    return root;
}

// Inserting words alphabetically (Lexicographical order)
void BST::insert(string val) {
    root = insertRec(root, val);
}

Node* BST::insertRec(Node* node, string val) {
    if (node == nullptr) {
        return new Node(val);
    }
    // If the word comes before the current node alphabetically, go left
    if (val < node->data) {
        node->left = insertRec(node->left, val);
    } 
    // If it comes after, go right
    else if (val > node->data) {
        node->right = insertRec(node->right, val);
    }
    return node;
}

// Searching to see if a word exists in the tree
bool BST::search(string val) {
    return searchRec(root, val);
}

bool BST::searchRec(Node* node, string val) {
    if (node == nullptr) return false;
    if (node->data == val) return true;
    
    if (val < node->data) return searchRec(node->left, val);
    return searchRec(node->right, val);
}

// Counting total nodes
int BST::countNodes() {
    return countNodesRec(root);
}

int BST::countNodesRec(Node* node) {
    if (node == nullptr) return 0;
    return 1 + countNodesRec(node->left) + countNodesRec(node->right);
}

// Getting tree height
int BST::getHeight() {
    return getHeightRec(root);
}

int BST::getHeightRec(Node* node) {
    if (node == nullptr) return 0;
    int leftHeight = getHeightRec(node->left);
    int rightHeight = getHeightRec(node->right);
    return 1 + max(leftHeight, rightHeight);
}