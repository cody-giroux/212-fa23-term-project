#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <fstream>
#include <unordered_map>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    int count;

    TrieNode() : count(0) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie();

    void insert(const std::string& word);

    std::pair<bool, int> search(const std::string& word);

    void generateDotFile(const std::string& filename);

private:
    void generateDot(TrieNode* node, std::ofstream& dotFile, const std::string& prefix);
};

#endif // TRIE_H