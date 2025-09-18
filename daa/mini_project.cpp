#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

mutex printMutex;
int threadCount = 0;

string arrToStr(const vector<int>& arr, int l, int r) {
    string s = "[";
    for (int i = l; i <= r; i++) {
        s += to_string(arr[i]);
        if (i < r) s += " ";
    }
    s += "]";
    return s;
}

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// -------- Single-threaded merge sort --------
void mergeSortSingle(vector<int>& arr, int l, int r, int depth) {
    {
        lock_guard<mutex> lock(printMutex);
        cout << string(depth * 3, ' ') << "[Main] Portion: " << arrToStr(arr, l, r) << "\n";
    }

    if (l >= r) return;

    int m = l + (r - l) / 2;

    mergeSortSingle(arr, l, m, depth + 1);
    mergeSortSingle(arr, m + 1, r, depth + 1);

    merge(arr, l, m, r);

    {
        lock_guard<mutex> lock(printMutex);
        cout << string(depth * 3, ' ') << "[Main] Merged: " << arrToStr(arr, l, r) << "\n";
    }
}

// -------- Multithreaded merge sort --------
void mergeSortMulti(vector<int>& arr, int l, int r, int depth, string tname) {
    {
        lock_guard<mutex> lock(printMutex);
        cout << string(depth * 3, ' ') << "[" << tname << "] Portion: " << arrToStr(arr, l, r) << "\n";
    }

    if (l >= r) return;

    int m = l + (r - l) / 2;

    string leftName = "T" + to_string(++threadCount);
    string rightName = "T" + to_string(++threadCount);

    thread leftThread(mergeSortMulti, ref(arr), l, m, depth + 1, leftName);
    mergeSortMulti(arr, m + 1, r, depth + 1, rightName);

    leftThread.join();

    merge(arr, l, m, r);

    {
        lock_guard<mutex> lock2(printMutex);
        cout << string(depth * 3, ' ') << "[" << tname << "] Merged: " << arrToStr(arr, l, r) << "\n";
    }
}

int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    cout << "Original Array: " << arrToStr(arr, 0, arr.size() - 1) << "\n\n";

    cout << "=== Single-threaded Merge Sort Visualization ===\n";
    vector<int> arr1 = arr;
    mergeSortSingle(arr1, 0, arr1.size() - 1, 0);

    cout << "\n=== Multi-threaded Merge Sort Visualization ===\n";
    vector<int> arr2 = arr;
    mergeSortMulti(arr2, 0, arr2.size() - 1, 0, "T0:Main");

    return 0;
}