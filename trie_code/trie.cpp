#include "trie.h"
#include <vector> 
#include <algorithm>


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
        current->prefixCount++;  // Increment prefix count at each node
    }
    current->isEndOfWord = true;
    current->count++;
}


Trie::trio Trie::search(const std::string& word) {
    TrieNode* current = root;
    int identicalCount = 0;
    int prefixCount = 0;
    //searches through the word and checks if the character in the word exist as a key in the childrent map and returns false
    // moves current to children node corresponding to character in word
    for (char ch : word) {
        ch = tolower(ch);
        if (current->children.find(ch) == current->children.end()) {
            return {false, 0};
        }
        current = current->children[ch];
        identicalCount = current->count;
        prefixCount = current->prefixCount;
    }
    return {current->isEndOfWord, identicalCount, prefixCount};
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
        generateDot(child.second, dotFile, prefix + child.first);
    }
}

std::vector<std::string> Trie::autocomplete(const std::string& prefix) {
    std::vector<std::string> result;
    TrieNode* current = root;

    // Traverse to the node corresponding to the prefix
    for (char ch : prefix) {
        ch = tolower(ch);
        if (current->children.find(ch) == current->children.end()) {
            return result; // Prefix not found
        }
        current = current->children[ch];
    }

    // Use BFS to find all complete words under  node
    std::queue<std::pair<TrieNode*, std::string>> bfsQueue;
    bfsQueue.push({current, prefix});
    // Opted out of recursive depth first search as queues were easier to wrap head around
    // Set max amount of words to be outputted to avoid possible issues with few letter searches
    int maxOutputWords = 20;
    while (( !bfsQueue.empty() ) && ( result.size() < maxOutputWords)) {
        auto currentPair = bfsQueue.front();
        bfsQueue.pop();

        TrieNode* currentNode = currentPair.first;
        std::string currentPrefix = currentPair.second;

        // Check if the current node is the end of a complete word
        if (currentNode->isEndOfWord) {
            result.push_back(currentPrefix);
        }

        for (const auto& child : currentNode->children) {
            bfsQueue.push({child.second, currentPrefix + child.first});
        }
    }

    return result;
}


