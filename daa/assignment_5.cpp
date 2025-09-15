#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


/*
    Problem Statement:
        Quick Sort using determined and randomized pivot.
*/


class QuickSort {
private:
    vector<int> arr;

    // Partition using last element as pivot
    int partitionLast(int low, int high) {
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

    // Partition using randomized pivot
    int partitionRandom(int low, int high) {
        int randIndex = low + rand() % (high - low + 1);
        swap(arr[randIndex], arr[high]);  // move random pivot to end
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

    // Recursive QuickSort (last element pivot)
    void quickSortLast(int low, int high) {
        if (low < high) {
            int pivotIndex = partitionLast(low, high);
            quickSortLast(low, pivotIndex - 1);
            quickSortLast(pivotIndex + 1, high);
        }
    }

    // Recursive QuickSort (randomized pivot)
    void quickSortRandom(int low, int high) {
        if (low < high) {
            int pivotIndex = partitionRandom(low, high);
            quickSortRandom(low, pivotIndex - 1);
            quickSortRandom(pivotIndex + 1, high);
        }
    }

public:
    QuickSort(const vector<int>& input) {
        arr = input;
    }

    void sortLastPivot() {
        quickSortLast(0, arr.size() - 1);
    }

    void sortRandomPivot() {
        quickSortRandom(0, arr.size() - 1);
    }

    void printArray() const {
        for (int x : arr) cout << x << " ";
        cout << endl;
    }
};


int main() {
    srand(time(0));  // seed random numbers for randomized QuickSort
    
    int choice;
    while (true) {
        cout << "\n--- QuickSort Menu ---\n";
        cout << "1. QuickSort with Last Element Pivot\n";
        cout << "2. QuickSort with Randomized Pivot\n";
        cout << "3. Exit\n";
        cout << "Response: ";
        cin >> choice;

        if (choice == 3) {
            cout << "Exiting program.\n";
            break;
        }

        int n;
        cout << "Enter number of elements: ";
        cin >> n;

        vector<int> userInput(n);
        cout << "Enter " << n << " elements: ";
        for (int i = 0; i < n; i++) cin >> userInput[i];

        QuickSort sorter(userInput);

        cout << "Original array: ";
        sorter.printArray();

        if (choice == 1) {
            sorter.sortLastPivot();
            cout << "Sorted using Last Element Pivot: ";
            sorter.printArray();
        }
        else if (choice == 2) {
            sorter.sortRandomPivot();
            cout << "Sorted using Randomized Pivot: ";
            sorter.printArray();
        }
        else {
            cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}