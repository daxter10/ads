#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

// Structure for a Suffix Tree Node
struct SuffixTreeNode {
    unordered_map<char, SuffixTreeNode*> children; // Map of child nodes
    int start;                                    // Start index of the substring
    int *end;                                    // End index of the substring
    SuffixTreeNode* suffixLink;                  // Suffix link for Ukkonen's algorithm

    SuffixTreeNode(int start, int *end) {
        this->start = start;
        this->end = end;
        this->suffixLink = nullptr;
    }

    int edgeLength() {
        return *end - start + 1;
    }
};

// Suffix Tree class
class SuffixTree {
private:
    string text;                   // The input text
    SuffixTreeNode *root;          // Root node of the suffix tree
    SuffixTreeNode *activeNode;    // Active node during construction
    int activeEdge;                // Active edge during construction
    int activeLength;              // Active length during construction
    int remainingSuffixCount;      // Remaining suffixes to insert
    int *leafEnd;                  // End of the current leaf
    int size;                      // Size of the input text

    // Function to extend the suffix tree by one character
    void extendSuffixTree(int pos);

    // Helper function to traverse the tree for pattern search
    bool traverseTree(SuffixTreeNode *node, const string &pattern, int &index);

    // Function to delete the suffix tree and free memory
    void deleteTree(SuffixTreeNode *node);

public:
    SuffixTree(const string &text);
    ~SuffixTree();

    // Function to search for a pattern in the text
    bool search(const string &pattern);
};

// Constructor
SuffixTree::SuffixTree(const string &text) {
    this->text = text;
    size = text.size();
    root = new SuffixTreeNode(-1, new int(-1));
    activeNode = root;
    activeEdge = -1;
    activeLength = 0;
    remainingSuffixCount = 0;
    leafEnd = new int(-1);

    // Build the suffix tree
    for (int i = 0; i < size; i++) {
        extendSuffixTree(i);
    }
}

// Destructor
SuffixTree::~SuffixTree() {
    deleteTree(root);
    delete leafEnd;
}

// Function to extend the suffix tree by one character
void SuffixTree::extendSuffixTree(int pos) {
    (*leafEnd) = pos;
    remainingSuffixCount++;

    SuffixTreeNode *lastNewNode = nullptr;

    while (remainingSuffixCount > 0) {
        if (activeLength == 0) activeEdge = pos;

        char currentChar = text[activeEdge];
        if (activeNode->children.find(currentChar) == activeNode->children.end()) {
            activeNode->children[currentChar] = new SuffixTreeNode(pos, leafEnd);

            if (lastNewNode != nullptr) {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = nullptr;
            }
        } else {
            SuffixTreeNode *next = activeNode->children[currentChar];
            if (activeLength >= next->edgeLength()) {
                activeEdge += next->edgeLength();
                activeLength -= next->edgeLength();
                activeNode = next;
                continue;
            }

            if (text[next->start + activeLength] == text[pos]) {
                if (lastNewNode != nullptr && activeNode != root) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
                activeLength++;
                break;
            }

            int *splitEnd = new int(next->start + activeLength - 1);
            SuffixTreeNode *split = new SuffixTreeNode(next->start, splitEnd);
            activeNode->children[currentChar] = split;

            split->children[text[pos]] = new SuffixTreeNode(pos, leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;

            if (lastNewNode != nullptr) {
                lastNewNode->suffixLink = split;
            }

            lastNewNode = split;
        }

        remainingSuffixCount--;

        if (activeNode == root && activeLength > 0) {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        } else if (activeNode != root) {
            activeNode = activeNode->suffixLink;
        }
    }
}

// Function to delete the suffix tree and free memory
void SuffixTree::deleteTree(SuffixTreeNode *node) {
    for (auto &child : node->children) {
        deleteTree(child.second);
    }
    delete node->end;
    delete node;
}

// Function to search for a pattern in the text
bool SuffixTree::search(const string &pattern) {
    int index = 0;
    return traverseTree(root, pattern, index);
}

// Helper function to traverse the tree for pattern search
bool SuffixTree::traverseTree(SuffixTreeNode *node, const string &pattern, int &index) {
    if (index == pattern.size()) return true;

    if (node->children.find(pattern[index]) == node->children.end()) return false;

    SuffixTreeNode *next = node->children[pattern[index]];
    int edgeLength = next->edgeLength();

    for (int i = 0; i < edgeLength && index < pattern.size(); i++) {
        if (text[next->start + i] != pattern[index]) return false;
        index++;
    }

    return traverseTree(next, pattern, index);
}

// Main function
int main() {
    string text, pattern;

    cout << "Enter the text: ";
    cin >> text;

    SuffixTree suffixTree(text);

    cout << "Enter the pattern to search: ";
    cin >> pattern;

    if (suffixTree.search(pattern)) {
        cout << "Pattern found in the text.\n";
    } else {
        cout << "Pattern not found in the text.\n";
    }

    return 0;
}
