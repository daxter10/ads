#include <iostream>
using namespace std;

// A B-Tree Node
class BTreeNode {
    int *keys;           // Array of keys
    int t;               // Minimum degree (defines the range for number of keys)
    BTreeNode **children; // Array of child pointers
    int n;               // Current number of keys
    bool leaf;           // True if leaf node

public:
    BTreeNode(int _t, bool _leaf);

    // Traverse all nodes in a subtree rooted with this node
    void traverse();

    // Search for a key in the subtree rooted with this node
    BTreeNode *search(int k);

    // Insert a key in a non-full node
    void insertNonFull(int k);

    // Split the child `i` of this node
    void splitChild(int i, BTreeNode *y);

    friend class BTree;
};

// A B-Tree
class BTree {
    BTreeNode *root; // Pointer to the root node
    int t;           // Minimum degree

public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    // Traverse the B-Tree
    void traverse() {
        if (root != nullptr)
            root->traverse();
    }

    // Search for a key in the B-Tree
    BTreeNode *search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    // Insert a new key in the B-Tree
    void insert(int k);
};

// Constructor for a BTreeNode
BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys = new int[2 * t - 1];
    children = new BTreeNode *[2 * t];

    n = 0;
}

// Function to traverse the B-Tree
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            children[i]->traverse();
        cout << keys[i] << " ";
    }

    if (!leaf)
        children[i]->traverse();
}

// Function to search for a key in the subtree rooted with this node
BTreeNode *BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf)
        return nullptr;

    return children[i]->search(k);
}

// Function to insert a new key in the B-Tree
void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);

            s->children[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);

            root = s;
        } else
            root->insertNonFull(k);
    }
}

// Function to insert a key in a non-full node
void BTreeNode::insertNonFull(int k) {
    int i = n - 1;

    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n++;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

// Function to split a child
void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n++;
}

// Main function
int main() {
    int t;
    cout << "Enter the minimum degree of the B-Tree: ";
    cin >> t;

    BTree btree(t);

    int choice, key;
    while (true) {
        cout << "\n1. Insert key\n2. Traverse B-Tree\n3. Search key\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the key to insert: ";
            cin >> key;
            btree.insert(key);
            break;
        case 2:
            cout << "B-Tree traversal: ";
            btree.traverse();
            cout << endl;
            break;
        case 3:
            cout << "Enter the key to search: ";
            cin >> key;
            if (btree.search(key) != nullptr)
                cout << "Key " << key << " is found in the B-Tree.\n";
            else
                cout << "Key " << key << " is not found in the B-Tree.\n";
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
}
