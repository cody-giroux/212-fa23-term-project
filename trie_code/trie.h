#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    int count;          // Count for the specific word
    int prefixCount;    // Count for words sharing the common prefix

    TrieNode() : isEndOfWord(false), count(0), prefixCount(0) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie();

    void insert(const std::string& word);

    std::pair<bool, int> search(const std::string& word);

    void generateDotFile(const std::string& filename);

    std::vector<std::string> autocomplete(const std::string& prefix);



private:
    void generateDot(TrieNode* node, std::ofstream& dotFile, const std::string& prefix);
};

#endif // TRIE_H
