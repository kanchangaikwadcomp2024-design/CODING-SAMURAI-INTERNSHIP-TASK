#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char d, int f) {
        data = d;
        freq = f;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, string code,
                   unordered_map<char, string>& huffmanCode) {
    if (!root)
        return;

    if (!root->left && !root->right)
        huffmanCode[root->data] = code;

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

void compress(string inputFile, string outputFile) {
    ifstream in(inputFile);
    if (!in) {
        cout << "Error opening input file!\n";
        return;
    }

    ofstream out(outputFile, ios::binary);
    if (!out) {
        cout << "Error creating output file!\n";
        return;
    }

    string text((istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>());

    unordered_map<char, int> freq;

    for (char ch : text)
        freq[ch]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : freq)
        pq.push(new Node(pair.first, pair.second));

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;

        pq.push(sum);
    }

    if (pq.empty()) {
        cout << "File is empty!\n";
        return;
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    string encoded = "";
    for (char ch : text)
        encoded += huffmanCode[ch];

    out << encoded;

    in.close();
    out.close();

    cout << "File Compressed Successfully!\n";
}

int main() {
    string inputFile, outputFile;

    cout << "Enter input file name: ";
    cin >> inputFile;

    cout << "Enter output file name: ";
    cin >> outputFile;

    compress(inputFile, outputFile);

    return 0;
}
