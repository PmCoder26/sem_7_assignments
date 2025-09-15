#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/*
    Problem Statement:
        0/1 Knapsack using dynamic programming.
*/


class Knapsack {
private:
    vector<int> values;   // stores item values
    vector<int> weights;  // stores item weights
    int capacity;         // knapsack capacity
    vector<vector<int>> memo; // DP table for memoization

    // Recursive function with memoization
    int knapSack_0_1(int cap, int idx) {
        // Base case: no items left or capacity full
        if (cap == 0 || idx < 0) {
            return 0;
        }

        // Return already computed value
        if (memo[idx][cap] != -1) {
            return memo[idx][cap];
        }

        // If current item can fit into knapsack
        if (weights[idx] <= cap) {
            // Option 1: include the item
            int includeItem = values[idx] + knapSack_0_1(cap - weights[idx], idx - 1);
            // Option 2: exclude the item
            int excludeItem = knapSack_0_1(cap, idx - 1);

            // Take maximum of both choices
            return memo[idx][cap] = max(includeItem, excludeItem);
        } else {
            // If item is too heavy, skip it
            return memo[idx][cap] = knapSack_0_1(cap, idx - 1);
        }
    }

public:
    // Constructor to read input
    Knapsack() {
        int n;
        cout << "Enter number of items: ";
        cin >> n;

        values.resize(n);
        weights.resize(n);

        cout << "Enter values of items: ";
        for (int i = 0; i < n; i++) {
            cin >> values[i];
        }

        cout << "Enter weights of items: ";
        for (int i = 0; i < n; i++) {
            cin >> weights[i];
        }

        cout << "Enter knapsack capacity: ";
        cin >> capacity;

        // Initialize memoization table with -1
        memo.assign(n, vector<int>(capacity + 1, -1));
    }

    // Public method to solve the problem
    int solve() {
        return knapSack_0_1(capacity, values.size() - 1);
    }
};

// Example usage
int main() {
    Knapsack ks; // constructor will take input
    cout << "Maximum value in knapsack = " << ks.solve() << endl;
    return 0;
}