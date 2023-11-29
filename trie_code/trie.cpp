#include "trie.h"

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const std::string& word) {
    TrieNode* current = root;
    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new TrieNode();
        }
        current = current->children[ch];
    }
    current->count++;
}

std::pair<bool, int> Trie::search(const std::string& word) {
    TrieNode* current = root;
    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            return {false, 0};
        }
        current = current->children[ch];
    }
    return {true, current->count};
}

void Trie::generateDotFile(const std::string& filename) {
    std::ofstream dotFile(filename);
    dotFile << "digraph Trie {\n";
    generateDot(root, dotFile, "");
    dotFile << "}\n";
    dotFile.close();
}

void Trie::generateDot(TrieNode* node, std::ofstream& dotFile, const std::string& prefix) {
    for (const auto& child : node->children) {
        dotFile << "  \"" << prefix << "\" -> \"" << prefix + child.first << "\";\n";
        generateDot(child.second,    dotFile, prefix + child.first);
    }
}
