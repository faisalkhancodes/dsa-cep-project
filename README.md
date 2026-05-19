# DSA CEP - Genetic Sequence Comparison System

**Student Name:** Faisal Khan
**Enrollment:** 01-131232-105
**Course:** CSC-221 - Data Structures & Algorithms
**Instructor:** Engr. Muhammad Nauman
**Semester:** 4 (Spring-2026)
**Department:** Computer Engineering, Bahria School of Engineering & Applied Sciences

---

## Project Overview

This C++ console application implements an **AI-assisted diagnostic system** for early detection of genetic disorders. It reads compressed gene-sequence logs from two independent diagnostic labs, constructs Binary Search Trees (BSTs) from the data, computes common patterns, generates difference files, calculates a similarity percentage, and produces a structured final report - all without using any C++ Standard Template Library (STL) containers.

---

## Three-File Architecture

| File | Role |
|------|------|
| `BST.h` | Class declaration - `Node` struct + `BST` class interface |
| `BST.cpp` | Full implementation of all BST methods (insert, search, count, height, collect) |
| `main.cpp` | Program entry point - file I/O, tree comparison, similarity calculation, report generation |

---

## Data Structures

### `struct Node`  *(BST.h)*
Each node stores:
| Field | Type | Purpose |
|-------|------|---------|
| `geneticSequence` | `string` | The gene-sequence payload |
| `leftChild` | `Node*` | Pointer to the left sub-tree (lexicographically smaller) |
| `rightChild` | `Node*` | Pointer to the right sub-tree (lexicographically larger) |

### `class BST`  *(BST.h / BST.cpp)*
| Method | Description |
|--------|-------------|
| `insert(val)` | Inserts a sequence using lexicographic ordering (recursive) |
| `search(val)` | Returns `true` if the sequence exists in the tree |
| `countNodes()` | Returns the total number of nodes (unique sequences) |
| `getHeight()` | Returns the maximum depth of the tree |
| `collectInorder(array, size)` | Fills a caller-supplied array in sorted order |
| `getRoot()` | Returns the root pointer for external traversal |

> **No STL containers** (`<vector>`, `<stack>`, `<queue>`, etc.) are used anywhere. Tree height uses a manual `?:` comparison instead of `std::max()`.

---

## Algorithm Walkthrough

### 1. File Input
```
ifstream fileLabA("lab_a_data.txt");
while (getline(fileLabA, line)) -> bst1.insert(line);

ifstream fileLabB("lab_b_data.txt");
while (getline(fileLabB, line)) -> bst2.insert(line);
```
Each line is one gene sequence. Empty lines are skipped.

### 2. BST Insertion (Lexicographic)
```
insertHelper(node, val):
    if node == null  -> return new Node(val)
    if val < node    -> go left
    if val > node    -> go right
    if val == node   -> skip (no duplicates)
```

### 3. Pattern Matching
In-order traversal of BST1; each sequence is searched in BST2:
- **Found in both** -> written to `common_patterns.txt`
- **Only in BST1**  -> written to `nc_element_bst1.txt`

Then BST2 is traversed, and sequences not found in BST1 are written to `nc_element_bst2.txt`.

### 4. Similarity Calculation - Jaccard Similarity Index

```
Similarity = |A n B| / |A u B|  x  100

Where:
  |A n B| = number of sequences common to both labs
  |A u B| = nodes(BST1) + nodes(BST2) - |A n B|
```

**Justification:** The Jaccard index is the standard bioinformatics metric for measuring overlap between two finite sample populations. It equals 100 % when datasets are identical and 0 % when they share nothing, providing a mathematically sound and interpretable similarity score.

| Score Range | Level |
|-------------|-------|
| >= 70 %    | High  |
| 40 - 69 %  | Medium |
| < 40 %     | Low   |

---

## Output Files

| File | Contents |
|------|----------|
| `common_patterns.txt` | Sequences in both labs, with length of each |
| `nc_element_bst1.txt` | Sequences exclusive to Lab A |
| `nc_element_bst2.txt` | Sequences exclusive to Lab B |
| `final_report.txt` | Full summary: metrics, similarity, observations, interpretation |

---

## How to Compile & Run

### Prerequisites
- GCC (MinGW) or any C++11-compatible compiler
- `lab_a_data.txt` and `lab_b_data.txt` in the same directory as the executable

### Command Line
```bash
g++ BST.cpp main.cpp -o cep_project
./cep_project          # Linux/macOS
cep_project.exe        # Windows
```

### VS Code
Press **F5** - the `.vscode/tasks.json` is pre-configured to compile and run automatically.

---

## Repository
[github.com/faisalkhancodes/dsa-cep-project](https://github.com/faisalkhancodes/dsa-cep-project)