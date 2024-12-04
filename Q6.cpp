#include <iostream>
#include <string>
using namespace std;

// Trie Node structure
class TrieNode {
public:
    TrieNode *children[26]; // Array of pointers to children nodes (26 letters for lowercase English)
    bool isEndOfWord;       // True if the node represents the end of a word

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

// Trie class
class Trie {
private:
    TrieNode *root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Function to insert a word into the Trie
    void insert(string word) {
        TrieNode *node = root;

        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }

        node->isEndOfWord = true;
        cout << "Inserted \"" << word << "\" into the Trie.\n";
    }

    // Function to search for a word in the Trie
    bool search(string word) {
        TrieNode *node = root;

        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index];
        }

        return node->isEndOfWord;
    }
};

// Main function
int main() {
    Trie trie;

    int choice;
    string word;

    while (true) {
        cout << "\n1. Insert word\n2. Search word\n3. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the word to insert: ";
            cin >> word;
            trie.insert(word);
            break;

        case 2:
            cout << "Enter the word to search: ";
            cin >> word;
            if (trie.search(word)) {
                cout << "The word \"" << word << "\" is found in the Trie.\n";
            } else {
                cout << "The word \"" << word << "\" is NOT found in the Trie.\n";
            }
            break;

        case 3:
            return 0;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
}
