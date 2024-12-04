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

// Partition the array around a pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Randomized partition: Chooses a random pivot and partitions the array
int randomizedPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

// Randomized Select algorithm
int randomizedSelect(int arr[], int low, int high, int i) {
    if (low == high) {
        return arr[low];
    }

    int pivotIndex = randomizedPartition(arr, low, high);
    int k = pivotIndex - low + 1; // Number of elements in the left partition

    if (i == k) {
        return arr[pivotIndex]; // The pivot is the i-th smallest element
    } else if (i < k) {
        return randomizedSelect(arr, low, pivotIndex - 1, i); // Look in the left partition
    } else {
        return randomizedSelect(arr, pivotIndex + 1, high, i - k); // Look in the right partition
    }
}

// Main function
int main() {
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator

    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int i;
    cout << "Enter the value of i (1-based index) to find the i-th smallest element: ";
    cin >> i;

    if (i < 1 || i > n) {
        cout << "Invalid value of i. Please enter a value between 1 and " << n << "." << endl;
        return 1;
    }

    int ithSmallest = randomizedSelect(arr, 0, n - 1, i);
    cout << "The " << i << "-th smallest element is: " << ithSmallest << endl;

    return 0;
}
