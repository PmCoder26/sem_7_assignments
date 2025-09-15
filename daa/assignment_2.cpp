#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;


/*
    Problem Statement:
        Huffman Encoding using Greedy Strategy.
*/

// Node for Huffman tree
class Node {
public:
    char symbol;     // character stored at leaf; for internal nodes this can be dummy
    int freq;        // frequency of this node (leaf or sum of leaves)
    Node* left;
    Node* right;

    Node(char s, int f, Node* l = nullptr, Node* r = nullptr)
        : symbol(s), freq(f), left(l), right(r) {}
};

// Comparator for priority queue (min-heap) based on frequency
struct NodeCompare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;  // smaller freq has higher priority
    }
};

class HuffmanCoding {
private:
    vector<char> chars;
    vector<int> freqs;
    Node* root;
    map<char, string> codes;

public:
    HuffmanCoding() : root(nullptr) {}

    // Read user input
    void takeInput() {
        int n;
        cout << "Enter the number of characters: ";
        cin >> n;
        chars.resize(n);
        freqs.resize(n);

        cout << "Enter characters and their frequencies:\n";
        for (int i = 0; i < n; i++) {
            cout << "Character " << (i + 1) << ": ";
            cin >> chars[i];
            cout << "Frequency of " << chars[i] << ": ";
            cin >> freqs[i];
        }
    }

    // Build Huffman tree (greedy, using priority queue)
    void buildTree() {
        auto t1 = high_resolution_clock::now();

        priority_queue<Node*, vector<Node*>, NodeCompare> pq;

        // make leaf node for each char and push to pq
        for (size_t i = 0; i < chars.size(); i++) {
            pq.push(new Node(chars[i], freqs[i]));
        }

        // until only one tree remains
        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();

            // merge two smallest frequency nodes
            Node* merged = new Node('\0', left->freq + right->freq, left, right);
            pq.push(merged);
        }

        // root of Huffman tree
        if (!pq.empty()) {
            root = pq.top();
        }

        auto t2 = high_resolution_clock::now();
        auto dur = duration_cast<microseconds>(t2 - t1);
        cout << "Huffman Tree Construction Elapsed Time: " << dur.count() << " microseconds\n";
    }

    // Traverse the tree to generate codes
    void generateCodes(Node* node, const string& prefix) {
        if (!node) return;

        // If leaf node, assign code
        if (!node->left && !node->right) {
            codes[node->symbol] = prefix != "" ? prefix : "0";  
            // (if only one character, assign “0” to avoid empty string)
        }

        generateCodes(node->left, prefix + "0");
        generateCodes(node->right, prefix + "1");
    }

    void calculateCodes() {
        auto t1 = high_resolution_clock::now();
        generateCodes(root, "");
        auto t2 = high_resolution_clock::now();
        auto dur = duration_cast<microseconds>(t2 - t1);
        cout << "Huffman Code Calculation Elapsed Time: " << dur.count() << " microseconds\n";
    }

    // Estimate space used (in bits/bytes) by encoded data
    void calculateSpace() {
        auto t1 = high_resolution_clock::now();

        long long totalBits = 0;
        for (size_t i = 0; i < chars.size(); i++) {
            char c = chars[i];
            int f = freqs[i];
            string code = codes[c];
            totalBits += (long long)code.length() * f;
        }
        double totalBytes = totalBits / 8.0;

        auto t2 = high_resolution_clock::now();
        auto dur = duration_cast<microseconds>(t2 - t1);
        cout << "Estimated space used for Huffman-encoded data: " << totalBits 
             << " bits (" << totalBytes << " bytes)\n";
        cout << "Space calculation elapsed time: " << dur.count() << " microseconds\n";
    }

    // Print final codes
    void printCodes() {
        cout << "\nHuffman Codes:\n";
        for (auto &p : codes) {
            cout << p.first << " -> " << p.second << "\n";
        }
    }
};

int main() {
    HuffmanCoding hc;
    hc.takeInput();
    hc.buildTree();
    hc.calculateCodes();
    hc.calculateSpace();
    hc.printCodes();
    return 0;
}