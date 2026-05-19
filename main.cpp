/*
    main.cpp
    This is the main program that runs the Genetic Sequence Comparison System.

    What this program does (step by step):
      1. Reads gene sequences from lab_a_data.txt and builds BST1 (Lab A)
      2. Reads gene sequences from lab_b_data.txt and builds BST2 (Lab B)
      3. Compares both trees to find common sequences and unique sequences
      4. Writes results to 3 output files
      5. Calculates similarity using the Jaccard formula
      6. Generates a final summary report

    Similarity Formula (Jaccard Similarity Index):
      Similarity = (Common sequences) / (Total unique sequences in both) x 100
      This method is used in bioinformatics to compare two sets of data.
      It gives 100% if both labs have exactly the same sequences,
      and 0% if they share nothing at all.

    Course   : CSC-221 Data Structures & Algorithms
    Instructor: Engr. Muhammad Nauman
    Student  : Faisal Khan | 01-131232-105
    Semester : 4 (Spring-2026)
*/

#include "BST.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>


using namespace std;

// Prints a line of repeated characters (used to make the output look neat)
void printSeparator(char ch = '=', int width = 60) {
  for (int i = 0; i < width; i++)
    cout << ch;
  cout << "\n";
}

// Trims trailing whitespace and carriage returns (\r) from a string
void trimSequence(string& str) {
  while (!str.empty() && (str.back() == '\r' || str.back() == ' ' || str.back() == '\t')) {
    str.pop_back();
  }
}

/*
    collectCommonAndUnique
    This function goes through every node in BST1 (in alphabetical order).
    For each sequence in BST1:
      - If it also exists in BST2 --> it is a COMMON pattern, save to commonFile
      - If it does NOT exist in BST2 --> it is unique to Lab A, save to
   unique1File
*/
void collectCommonAndUnique(Node *node, BST &bst2, ofstream &commonFile,
                            ofstream &unique1File, int &commonCount) {
  if (node == nullptr)
    return; // base case: reached an empty branch, stop

  // visit left side first (in-order traversal)
  collectCommonAndUnique(node->leftChild, bst2, commonFile, unique1File,
                         commonCount);

  // check if this sequence also exists in BST2
  if (bst2.search(node->geneticSequence)) {
    // found in both trees -- write to common patterns file
    commonFile << node->geneticSequence
               << "  |  Length: " << node->geneticSequence.length() << "\n";
    commonCount++; // keep track of how many common ones we found
  } else {
    // not in BST2 -- this sequence is unique to Lab A only
    unique1File << node->geneticSequence << "\n";
  }

  // visit right side last
  collectCommonAndUnique(node->rightChild, bst2, commonFile, unique1File,
                         commonCount);
}

/*
    collectUniqueInBST2
    This function goes through every node in BST2.
    For each sequence in BST2:
      - If it does NOT exist in BST1 --> it is unique to Lab B, save to
   unique2File
      - If it already exists in BST1 --> skip it (already counted as common
   above)
*/
void collectUniqueInBST2(Node *node, BST &bst1, ofstream &unique2File) {
  if (node == nullptr)
    return; // base case: empty branch, stop

  collectUniqueInBST2(node->leftChild, bst1, unique2File);

  // only save if this sequence is NOT in BST1
  if (!bst1.search(node->geneticSequence))
    unique2File << node->geneticSequence << "\n";

  collectUniqueInBST2(node->rightChild, bst1, unique2File);
}

/*
    printInorder
    Prints all sequences stored in a BST to the screen, in sorted order,
    with a number in front of each one (1, 2, 3...)
*/
void printInorder(Node *node, int &counter) {
  if (node == nullptr)
    return;
  printInorder(node->leftChild, counter);
  cout << "  " << counter++ << ". " << node->geneticSequence << "\n";
  printInorder(node->rightChild, counter);
}

// =======================================================================
// main function -- the program starts here
// =======================================================================
int main() {

  // Create two empty BSTs -- one for each lab
  BST bst1; // Lab A (Genomic Research Unit A -- Northern Region)
  BST bst2; // Lab B (Genomic Research Unit B -- Southern Region)

  string line;

  // ---------------------------------------------------------------
  // STEP 1: Read Lab A data file and insert each sequence into BST1
  // ---------------------------------------------------------------
  ifstream fileA("lab_a_data.txt");
  if (!fileA.is_open()) {
    cout
        << "[ERROR] Cannot open lab_a_data.txt -- make sure the file exists.\n";
    return 1;
  }
  int linesA = 0;
  while (getline(fileA, line)) {
    trimSequence(line); // remove \r and hidden spaces
    if (!line.empty()) { // skip blank lines
      if (bst1.insert(line)) {
        linesA++;
      }
    }
  }
  fileA.close();

  // ---------------------------------------------------------------
  // STEP 2: Read Lab B data file and insert each sequence into BST2
  // ---------------------------------------------------------------
  ifstream fileB("lab_b_data.txt");
  if (!fileB.is_open()) {
    cout
        << "[ERROR] Cannot open lab_b_data.txt -- make sure the file exists.\n";
    return 1;
  }
  int linesB = 0;
  while (getline(fileB, line)) {
    trimSequence(line); // remove \r and hidden spaces
    if (!line.empty()) {
      if (bst2.insert(line)) {
        linesB++;
      }
    }
  }
  fileB.close();

  // ---------------------------------------------------------------
  // STEP 3: Get structural information from both trees
  // ---------------------------------------------------------------
  int totalA = bst1.countNodes(); // total unique sequences in Lab A
  int totalB = bst2.countNodes(); // total unique sequences in Lab B
  int heightA = bst1.getHeight(); // how tall BST1 is
  int heightB = bst2.getHeight(); // how tall BST2 is

  // ---------------------------------------------------------------
  // STEP 4: Open the three output files
  // ---------------------------------------------------------------
  ofstream commonFile("common_patterns.txt");
  ofstream unique1File("nc_element_bst1.txt");
  ofstream unique2File("nc_element_bst2.txt");

  if (!commonFile.is_open() || !unique1File.is_open() ||
      !unique2File.is_open()) {
    cout << "[ERROR] Could not create one or more output files.\n";
    return 1;
  }

  // Write a nice header at the top of each file
  commonFile
      << "============================================================\n"
      << "  COMMON GENETIC PATTERNS (found in BOTH Lab A and Lab B)\n"
      << "  Student : Faisal Khan  |  01-131232-105\n"
      << "============================================================\n"
      << "  Format  : SEQUENCE  |  Length\n"
      << "------------------------------------------------------------\n";

  unique1File
      << "============================================================\n"
      << "  SEQUENCES ONLY IN LAB A  (not found in Lab B)\n"
      << "============================================================\n";

  unique2File
      << "============================================================\n"
      << "  SEQUENCES ONLY IN LAB B  (not found in Lab A)\n"
      << "============================================================\n";

  // ---------------------------------------------------------------
  // STEP 5: Compare the two trees and write results to files
  // ---------------------------------------------------------------
  int commonCount = 0;

  // Go through BST1 and check each sequence against BST2
  collectCommonAndUnique(bst1.getRoot(), bst2, commonFile, unique1File,
                         commonCount);

  // Go through BST2 and find sequences that BST1 does not have
  collectUniqueInBST2(bst2.getRoot(), bst1, unique2File);

  // Write the total count and close each file neatly
  commonFile
      << "------------------------------------------------------------\n"
      << "  Total common sequences : " << commonCount << "\n"
      << "============================================================\n";
  unique1File
      << "============================================================\n";
  unique2File
      << "============================================================\n";

  commonFile.close();
  unique1File.close();
  unique2File.close();

  // ---------------------------------------------------------------
  // STEP 6: Calculate similarity using the Jaccard Similarity Index
  //
  // Formula : Similarity = Common / (Total_A + Total_B - Common) x 100
  // Example : if 3 common out of 7 total unique --> 3/7 x 100 = 42.86%
  //
  // This formula is standard in bioinformatics for comparing gene sets.
  // ---------------------------------------------------------------
  int unionSize =
      totalA + totalB - commonCount; // total unique sequences across both labs
  double similarity = 0.0;
  if (unionSize > 0)
    similarity = ((double)commonCount / unionSize) * 100.0;

  // Classify the similarity into a human-readable level
  string level;
  if (similarity >= 70.0)
    level = "High";
  else if (similarity >= 40.0)
    level = "Medium";
  else
    level = "Low";

  int exclusiveA = totalA - commonCount; // sequences only in Lab A
  int exclusiveB = totalB - commonCount; // sequences only in Lab B

  // ---------------------------------------------------------------
  // STEP 7: Write the final summary report to final_report.txt
  // ---------------------------------------------------------------
  ofstream report("final_report.txt");
  if (!report.is_open()) {
    cout << "[ERROR] Cannot create final_report.txt\n";
    return 1;
  }

  report
      << "============================================================\n"
      << "         FINAL ANALYSIS SUMMARY REPORT\n"
      << "         AI-Assisted Genetic Disorder Diagnostic System\n"
      << "============================================================\n"
      << "  Project   : CEP - Genetic Sequence Comparison System\n"
      << "  Course    : CSC-221 - Data Structures & Algorithms\n"
      << "  Instructor: Engr. Muhammad Nauman  |  Spring-2026\n"
      << "  Student   : Faisal Khan  |  01-131232-105\n"
      << "============================================================\n\n"

      << "------------------------------------------------------------\n"
      << "  SECTION 1 : STRUCTURAL METRICS\n"
      << "------------------------------------------------------------\n"
      << "  BST1 (Lab A - Genomic Research Unit A)\n"
      << "    Total nodes (unique sequences) : " << totalA << "\n"
      << "    Tree height                    : " << heightA << "\n\n"
      << "  BST2 (Lab B - Genomic Research Unit B)\n"
      << "    Total nodes (unique sequences) : " << totalB << "\n"
      << "    Tree height                    : " << heightB << "\n\n"

      << "------------------------------------------------------------\n"
      << "  SECTION 2 : SIMILARITY MEASUREMENT\n"
      << "------------------------------------------------------------\n"
      << "  Method  : Jaccard Similarity Index\n"
      << "  Formula : Common / (Total_A + Total_B - Common) x 100\n\n"
      << "  Common sequences      : " << commonCount << "\n"
      << "  Total unique (union)  : " << unionSize << "\n"
      << "  Similarity Score      : " << fixed << setprecision(2) << similarity
      << "%\n"
      << "  Similarity Level      : " << level << "\n\n"

      << "------------------------------------------------------------\n"
      << "  SECTION 3 : OBSERVATIONS ABOUT COMMON PATTERNS\n"
      << "------------------------------------------------------------\n"
      << "  - " << commonCount
      << " gene sequence(s) are shared between Lab A and Lab B.\n"
      << "  - These shared sequences may indicate common genetic markers\n"
      << "    found in patients across both the Northern and Southern "
         "regions.\n"
      << "  - See common_patterns.txt for the full list with lengths.\n\n"

      << "------------------------------------------------------------\n"
      << "  SECTION 4 : DIFFERENCES BETWEEN DATASETS\n"
      << "------------------------------------------------------------\n"
      << "  - Lab A has " << exclusiveA
      << " unique sequence(s) not present in Lab B.\n"
      << "    (see nc_element_bst1.txt)\n"
      << "  - Lab B has " << exclusiveB
      << " unique sequence(s) not present in Lab A.\n"
      << "    (see nc_element_bst2.txt)\n"
      << "  - These differences suggest region-specific genetic variations.\n\n"

      << "------------------------------------------------------------\n"
      << "  SECTION 5 : INTERPRETATION OF SYSTEM CONSISTENCY\n"
      << "------------------------------------------------------------\n"
      << "  - Both trees were built correctly using alphabetical insertion.\n"
      << "  - Similarity score: " << fixed << setprecision(2) << similarity
      << "%  -->  Level: " << level << "\n";

  // Write a different conclusion depending on the similarity level
  if (level == "High")
    report << "  - The two datasets are very similar. Shared diagnostic\n"
           << "    models can be applied across both regions.\n";
  else if (level == "Medium")
    report << "  - The datasets have moderate overlap. Some diagnostic\n"
           << "    models may work cross-regionally with adjustments.\n";
  else
    report << "  - The datasets are mostly different. Separate diagnostic\n"
           << "    models should be built for each region.\n";

  report << "  - All 4 output files were generated successfully.\n"
         << "  - No STL containers were used; only raw BST node pointers.\n\n"
         << "============================================================\n"
         << "  END OF REPORT\n"
         << "============================================================\n";

  report.close();

  // ---------------------------------------------------------------
  // STEP 8: Print a summary to the console screen
  // ---------------------------------------------------------------
  printSeparator('=');
  cout << "   GENETIC SEQUENCE COMPARISON SYSTEM - OUTPUT\n";
  cout << "   Bahria University | CSC-221 | Spring-2026\n";
  printSeparator('=');

  // Show Lab A tree info
  cout << "\n[BST1 - Lab A]  Total valid sequences: " << linesA << "\n";
  cout << "  Unique sequences : " << totalA << "  |  Tree height: " << heightA
       << "\n";
  cout << "  Sequences in sorted order:\n";
  int c1 = 1;
  printInorder(bst1.getRoot(), c1);

  // Show Lab B tree info
  cout << "\n[BST2 - Lab B]  Total valid sequences: " << linesB << "\n";
  cout << "  Unique sequences : " << totalB << "  |  Tree height: " << heightB
       << "\n";
  cout << "  Sequences in sorted order:\n";
  int c2 = 1;
  printInorder(bst2.getRoot(), c2);

  // Show comparison results
  printSeparator('-');
  cout << "  Common sequences        : " << commonCount << "\n";
  cout << "  Total unique (union)    : " << unionSize << "\n";
  cout << "  Only in Lab A           : " << exclusiveA << "\n";
  cout << "  Only in Lab B           : " << exclusiveB << "\n";
  printSeparator('-');
  cout << "  Similarity Score : " << fixed << setprecision(2) << similarity
       << "%\n";
  cout << "  Similarity Level : " << level << "\n";
  printSeparator('=');

  cout << "\n  Output files created:\n"
       << "    >> common_patterns.txt\n"
       << "    >> nc_element_bst1.txt\n"
       << "    >> nc_element_bst2.txt\n"
       << "    >> final_report.txt\n";
  printSeparator('=');

  cout << "\nPress Enter to exit...\n";
  cin.get();
  return 0;
}