#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/*
    Problem Statement:
        Fractional Knapsack using Greedy Strategy.
*/


class FractionalKnapsack {
private:
    vector<int> values;
    vector<int> weights;
    vector<vector<double>> ratios;
    int capacity;

public:
    // Constructor to take user input
    FractionalKnapsack() {
        int n;
        cout << "Enter number of items: ";
        cin >> n;

        values.resize(n);
        weights.resize(n);
        ratios.resize(n, vector<double>(2));

        cout << "Enter values of items: ";
        for (int i = 0; i < n; i++) cin >> values[i];

        cout << "Enter weights of items: ";
        for (int i = 0; i < n; i++) cin >> weights[i];

        cout << "Enter knapsack capacity: ";
        cin >> capacity;

        // calculating value/weight ratios and storing
        for (int i = 0; i < n; i++) {
            ratios[i][0] = i; // index
            ratios[i][1] = (double)values[i] / (double)weights[i];
        }

        // sort ratios array by value/weight ratio in ascending order
        sort(ratios.begin(), ratios.end(),
             [](const vector<double>& a, const vector<double>& b) {
                 return a[1] < b[1];
             });
    }

    // recursive fractional knapsack
    int fracKnapsack(int i, int cap) {
        if (i < 0 || cap <= 0) return 0;

        int idx = (int)ratios[i][0]; // item index
        int netValue = 0;

        // if whole item can fit
        if (weights[idx] <= cap) {
            netValue += values[idx];
            return netValue + fracKnapsack(i - 1, cap - weights[idx]);
        }
        else { 
            // if only fraction of item can fit
            netValue = (int)(ratios[i][1] * cap);
            return netValue;
        }
    }

    void solve() {
        int n = values.size();
        int result = fracKnapsack(n - 1, capacity);
        cout << "The maximum value gained is: " << result << endl;
    }
};

int main() {
    FractionalKnapsack knap;
    knap.solve();
    return 0;
}