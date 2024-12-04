#include <iostream>
#include <vector>
using namespace std;

// Function to compute the Longest Prefix Suffix (LPS) array
void computeLPS(const string &pattern, vector<int> &lps) {
    int length = 0; // length of the previous longest prefix suffix
    lps[0] = 0;     // lps[0] is always 0
    int i = 1;

    while (i < pattern.length()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                // Backtrack the length
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to implement the KMP algorithm
void KMPAlgorithm(const string &text, const string &pattern) {
    int n = text.length();
    int m = pattern.length();

    // Create the LPS array
    vector<int> lps(m);
    computeLPSArray(pattern, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1]; // Get the next position from LPS array
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1]; // Backtrack in the pattern
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text, pattern;
    
    cout << "Enter the text: ";
    cin >> text;
    
    cout << "Enter the pattern to search: ";
    cin >> pattern;

    KMPAlgorithm(text, pattern);

    return 0;
}

