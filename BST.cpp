/*
    BST.cpp
    This file contains the actual working code for all BST operations.
    No STL containers are used anywhere -- only raw pointers and recursion.

    Course   : CSC-221 Data Structures & Algorithms
    Student  : Faisal Khan | 01-131232-105
    Semester : 4 (Spring-2026)
*/

#include "BST.h"

// ---------------------------------------------------------------
// Constructor: when a BST object is created, start with an empty tree
// ---------------------------------------------------------------
BST::BST() {
    rootNode = nullptr;
}

// ---------------------------------------------------------------
// Destructor: when the program ends, free all memory used by the tree
// ---------------------------------------------------------------
BST::~BST() {
    destroyHelper(rootNode);
}

// This function deletes all nodes one by one using post-order traversal
// (it deletes children first, then the parent -- safest order)
void BST::destroyHelper(Node* node) {
    if (node == nullptr) return;
    destroyHelper(node->leftChild);   // delete left side first
    destroyHelper(node->rightChild);  // then delete right side
    delete node;                      // finally delete this node
}

// ---------------------------------------------------------------
// getRoot: gives access to the top node so we can traverse from outside
// ---------------------------------------------------------------
Node* BST::getRoot() const {
    return rootNode;
}

// ---------------------------------------------------------------
// insert: adds a new gene sequence to the tree in alphabetical order
// ---------------------------------------------------------------
void BST::insert(string val) {
    rootNode = insertHelper(rootNode, val);
}

// This recursive function finds the correct position for the new sequence.
// If the value is smaller, go left. If larger, go right. If equal, skip (no duplicates).
Node* BST::insertHelper(Node* node, string val) {
    if (node == nullptr)
        return new Node(val);   // empty spot found -- place the new node here

    if (val < node->geneticSequence)
        node->leftChild  = insertHelper(node->leftChild,  val);  // go left
    else if (val > node->geneticSequence)
        node->rightChild = insertHelper(node->rightChild, val);  // go right
    // if val == node value, do nothing (no duplicate sequences allowed)

    return node;
}

// ---------------------------------------------------------------
// search: checks if a given gene sequence exists in the tree
// Returns true if found, false if not found
// ---------------------------------------------------------------
bool BST::search(string val) const {
    return searchHelper(rootNode, val);
}

// Recursively compares the value at each node and moves left or right
bool BST::searchHelper(Node* node, string val) const {
    if (node == nullptr)              return false;  // reached end, not found
    if (node->geneticSequence == val) return true;   // match found

    if (val < node->geneticSequence)
        return searchHelper(node->leftChild,  val);  // search left side
    return searchHelper(node->rightChild, val);       // search right side
}

// ---------------------------------------------------------------
// countNodes: counts how many gene sequences are stored in the tree
// ---------------------------------------------------------------
int BST::countNodes() const {
    return countHelper(rootNode);
}

// Add 1 for the current node, then count left and right subtrees
int BST::countHelper(Node* node) const {
    if (node == nullptr) return 0;
    return 1 + countHelper(node->leftChild) + countHelper(node->rightChild);
}

// ---------------------------------------------------------------
// getHeight: returns the height (depth) of the tree
// A tree with only one node has height 1
// ---------------------------------------------------------------
int BST::getHeight() const {
    return heightHelper(rootNode);
}

// Compare left and right heights manually (no std::max used -- STL is banned)
int BST::heightHelper(Node* node) const {
    if (node == nullptr) return 0;
    int leftHeight  = heightHelper(node->leftChild);
    int rightHeight = heightHelper(node->rightChild);
    // return whichever side is taller, plus 1 for the current node
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// ---------------------------------------------------------------
// collectInorder: fills an array with all sequences in sorted order
// (in-order traversal = left, then current, then right)
// ---------------------------------------------------------------
void BST::collectInorder(string* arr, int& size) const {
    inorderHelper(rootNode, arr, size);
}

void BST::inorderHelper(Node* node, string* arr, int& idx) const {
    if (node == nullptr) return;
    inorderHelper(node->leftChild,  arr, idx);   // visit left first
    arr[idx++] = node->geneticSequence;           // store current value
    inorderHelper(node->rightChild, arr, idx);   // then visit right
}