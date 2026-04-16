#include <iostream>
#include <string>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;
    
    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
    }
};

class Trie {
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == NULL) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == NULL) {
                return false;
            }
            node = node->children[index];
        }
        return node->isEndOfWord;
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (node->children[index] == NULL) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }
};

int main() {
    Trie* trie = new Trie();
    
    trie->insert("apple");
    cout << "search(\"apple\"): " << (trie->search("apple") ? "true" : "false") << endl;   // return True
    cout << "search(\"app\"): " << (trie->search("app") ? "true" : "false") << endl;     // return False
    cout << "startsWith(\"app\"): " << (trie->startsWith("app") ? "true" : "false") << endl; // return True
    trie->insert("app");
    cout << "search(\"app\"): " << (trie->search("app") ? "true" : "false") << endl;     // return True
    
    delete trie;
    return 0;
}
