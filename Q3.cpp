#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    vector<Edge> edges;
};

// Structure to represent a subset for Union-Find
struct Subset {
    int parent;
    int rank;
};

// Function to find the subset of an element `u` using path compression
int find(Subset subsets[], int u) {
    if (subsets[u].parent != u) {
        subsets[u].parent = find(subsets, subsets[u].parent);
    }
    return subsets[u].parent;
}

// Function to perform the union of two subsets using rank
void Union(Subset subsets[], int u, int v) {
    int rootU = find(subsets, u);
    int rootV = find(subsets, v);

    if (subsets[rootU].rank < subsets[rootV].rank) {
        subsets[rootU].parent = rootV;
    } else if (subsets[rootU].rank > subsets[rootV].rank) {
        subsets[rootV].parent = rootU;
    } else {
        subsets[rootV].parent = rootU;
        subsets[rootU].rank++;
    }
}

// Comparator function to sort edges by weight
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Function to compute the MST using Kruskal's Algorithm
void KruskalMST(Graph &graph) {
    int V = graph.V;
    vector<Edge> result; // Store the edges of the MST
    int e = 0;           // Counter for edges in the MST
    int i = 0;           // Counter for sorted edges

    // Step 1: Sort all edges by weight
    sort(graph.edges.begin(), graph.edges.end(), compareEdges);

    // Allocate memory for subsets
    Subset *subsets = new Subset[V];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Step 2: Pick the smallest edge and add it to the MST
    while (e < V - 1 && i < graph.E) {
        Edge nextEdge = graph.edges[i++];
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // If including this edge doesn't form a cycle
        if (x != y) {
            result.push_back(nextEdge);
            Union(subsets, x, y);
            e++;
        }
    }

    // Print the MST
    cout << "Edges in the Minimum Spanning Tree:" << endl;
    int totalWeight = 0;
    for (auto edge : result) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Total weight of the Minimum Spanning Tree: " << totalWeight << endl;

    delete[] subsets;
}

// Main function
int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph graph;
    graph.V = V;
    graph.E = E;

    cout << "Enter the edges (source, destination, weight):" << endl;
    for (int i = 0; i < E; i++) {
        Edge edge;
        cin >> edge.src >> edge.dest >> edge.weight;
        graph.edges.push_back(edge);
    }

    KruskalMST(graph);

    return 0;
}
