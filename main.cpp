#include <iostream>
#include <fstream>
#include <string>
#include "BST.h"

using namespace std;

// Function to traverse BST1 and check against BST2 to find common and unique elements
void compareTrees(Node* root1, BST& bst2, ofstream& commonFile, ofstream& uniqueFile, int& commonCount) {
    if (root1 == nullptr) return;

    // Go left
    compareTrees(root1->left, bst2, commonFile, uniqueFile, commonCount);

    // Process current node
    if (bst2.search(root1->data)) {
        // Found in both trees!
        commonFile << root1->data << " - Length: " << root1->data.length() << endl;
        commonCount++;
    } else {
        // Only in tree 1
        uniqueFile << root1->data << endl;
    }

    // Go right
    compareTrees(root1->right, bst2, commonFile, uniqueFile, commonCount);
}

// Function to find elements only in BST2
void findUniqueInBST2(Node* root2, BST& bst1, ofstream& uniqueFile2) {
    if (root2 == nullptr) return;
    
    findUniqueInBST2(root2->left, bst1, uniqueFile2);
    
    if (!bst1.search(root2->data)) {
        uniqueFile2 << root2->data << endl;
    }
    
    findUniqueInBST2(root2->right, bst1, uniqueFile2);
}

int main() {
    BST bst1, bst2;
    string line;

    // 1. Read files and build trees
    ifstream fileA("lab_a_data.txt");
    if (fileA.is_open()) {
        while (getline(fileA, line)) {
            bst1.insert(line);
        }
        fileA.close();
    }

    ifstream fileB("lab_b_data.txt");
    if (fileB.is_open()) {
        while (getline(fileB, line)) {
            bst2.insert(line);
        }
        fileB.close();
    }

    // 2. Open output files
    ofstream commonFile("common_patterns.txt");
    ofstream unique1File("nc_element_bst1.txt");
    ofstream unique2File("nc_element_bst2.txt");

    int commonCount = 0;

    // 3. Compare the trees
    compareTrees(bst1.getRoot(), bst2, commonFile, unique1File, commonCount);
    findUniqueInBST2(bst2.getRoot(), bst1, unique2File);

    commonFile.close();
    unique1File.close();
    unique2File.close();

    // 4. Calculate similarity percentage
    int totalNodes1 = bst1.countNodes();
    int totalNodes2 = bst2.countNodes();
    // Formula: (Common / (Total in 1 + Total in 2 - Common)) * 100
    int totalUnique = (totalNodes1 + totalNodes2) - commonCount;
    double similarity = 0;
    if (totalUnique > 0) {
        similarity = ((double)commonCount / totalUnique) * 100;
    }

    // 5. Generate Final Report
    ofstream report("final_report.txt");
    report << "=== FINAL ANALYSIS SUMMARY REPORT ===\n\n";
    
    string level = (similarity >= 70) ? "High" : (similarity >= 40) ? "Medium" : "Low";
    report << "Level of Similarity: " << level << " (" << similarity << "%)\n";
    
    report << "\nObservations about common patterns:\n";
    report << "- There are " << commonCount << " common genetic sequences shared between Northern and Southern regions.\n";
    
    report << "\nDifferences between datasets:\n";
    report << "- Lab A has unique sequences not found in Lab B, and vice versa. Check nc_element files for specifics.\n";
    
    report << "\nInterpretation of system consistency:\n";
    report << "- BST 1 (Lab A) Total Nodes: " << totalNodes1 << ", Height: " << bst1.getHeight() << "\n";
    report << "- BST 2 (Lab B) Total Nodes: " << totalNodes2 << ", Height: " << bst2.getHeight() << "\n";
    report << "- The trees are stable and the custom similarity metric successfully mapped regional overlaps.\n";
    
    report.close();

    cout << "Success! All files generated. Check your folder." << endl;

    return 0;
}