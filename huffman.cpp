#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Node structure for Huffman tree
struct Node {
    char data;
    int freq;
    Node *left, *right;
    Node(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

// Custom comparator for priority queue
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

//  Huffman using priority queue
Node* buildHuffmanTree(string S, vector<int>& f) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    // Create a leaf node for each character and add it to the priority queue
    for (int i = 0; i < S.length(); i++) {
        pq.push(new Node(S[i], f[i]));
    }
    
    // Huffman tree by combining nodes
    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        
        Node *parent = new Node('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }
    
    return pq.top();
}

// Function to print Huffman codes in preorder traversal
void printCodes(Node* root, string str) {
    if (!root) return;
    
    // If this is a leaf node, print the character and its code
    if (root->data != '$') {
        cout << root->data << ": " << str << endl;
    }
    
    // Traverse left and right children
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

int main() {
    string S = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};
    
    cout << "Input:\n";
    cout << "S = \"" << S << "\"\n";
    cout << "f[] = {";
    for (int i = 0; i < f.size(); i++) {
        cout << f[i];
        if (i < f.size() - 1) cout << ", ";
    }
    cout << "}\n\n";

    Node* root = buildHuffmanTree(S, f);
    
    cout << "Huffman Codes (Preorder Traversal):\n";
    printCodes(root, "");
    
    return 0;
}
