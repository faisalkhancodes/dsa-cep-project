#ifndef BST_H
#define BST_H
#include <string>

using namespace std;

// The basic building block of your tree
struct Node {
    string data;
    Node* left;
    Node* right;
    
    Node(string val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;
    
    // Hidden helper functions
    Node* insertRec(Node* node, string val);
    int countNodesRec(Node* node);
    int getHeightRec(Node* node);
    bool searchRec(Node* node, string val);

public:
    BST();
    ~BST();
    void insert(string val);
    int countNodes();
    int getHeight();
    bool search(string val);
    Node* getRoot();
};

#endif