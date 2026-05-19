/*
    BST.h
    This file defines the Node structure and the BST class.
    The BST stores gene sequences in alphabetical (A-Z) order.

    Course   : CSC-221 Data Structures & Algorithms
    Student  : Faisal Khan | 01-131232-105
    Semester : 4 (Spring-2026)
*/

#ifndef BST_H
#define BST_H

#include <string>
using namespace std;

// Each Node stores one gene sequence and two pointers to child nodes
struct Node {
    string geneticSequence;   // the gene sequence stored at this node
    Node*  leftChild;         // points to smaller sequences (left side)
    Node*  rightChild;        // points to larger sequences (right side)

    // When a new Node is created, set the value and make both children empty
    Node(string val) {
        geneticSequence = val;
        leftChild       = nullptr;
        rightChild      = nullptr;
    }
};

// The BST class manages the whole tree
// It can insert, search, count, and measure the height of the tree
class BST {
private:
    Node* rootNode;   // the starting (top) node of the tree

    // These helper functions do the real recursive work (hidden from outside)
    Node* insertHelper   (Node* node, string val);
    bool  searchHelper   (Node* node, string val) const;
    int   countHelper    (Node* node)              const;
    int   heightHelper   (Node* node)              const;
    void  destroyHelper  (Node* node);
    void  inorderHelper  (Node* node, string* arr, int& idx) const;

public:
    BST();    // sets up an empty tree
    ~BST();   // cleans up memory when the program ends

    void  insert         (string val);             // add a gene sequence
    bool  search         (string val) const;       // check if a sequence exists
    int   countNodes     ()           const;       // how many sequences are stored
    int   getHeight      ()           const;       // how tall the tree is
    Node* getRoot        ()           const;       // get the top node (for traversal)
    void  collectInorder (string* arr, int& size) const; // fill array in sorted order
};

#endif