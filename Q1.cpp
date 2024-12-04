#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to swap two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function to partition the array around a pivot
int partition(int arr[], int low, int high, int &comparisons) {
    int pivot = arr[high]; // Pivot element
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++; // Increment comparison count
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Function to choose a random pivot and partition the array
int randomizedPartition(int arr[], int low, int high, int &comparisons) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high, comparisons);
}

// Function implementing Randomized Quick Sort
void randomizedQuickSort(int arr[], int low, int high, int &comparisons) {
    if (low < high) {
        int pivotIndex = randomizedPartition(arr, low, high, comparisons);
        randomizedQuickSort(arr, low, pivotIndex - 1, comparisons);
        randomizedQuickSort(arr, pivotIndex + 1, high, comparisons);
    }
}

// Main function
int main() {
    srand(static_cast<unsigned>(time(0))); // Seed for random number generator

    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int comparisons = 0; // Variable to track the number of comparisons
    randomizedQuickSort(arr, 0, n - 1, comparisons);

    cout << "Sorted array:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Number of comparisons: " << comparisons << endl;

    return 0;
}
