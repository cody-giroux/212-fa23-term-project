#include "trie.h"

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const std::string& word) {
    TrieNode* current = root;
    //loops through all the characters in the word to check if the character in word exist as a key in the children map
    for (char ch : word) {
        ch = tolower(ch);
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new TrieNode();
        }
        current = current->children[ch];
        current->count++;
    }
}

std::pair<bool, int> Trie::search(const std::string& word) {
    TrieNode* current = root;
    //searches through the word and checks if the character in the word exist as a key in the childrent map and returns false 
    // moves current to children node corresponding to character in word
    for (char ch : word) {
        ch = tolower(ch);
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

std::vector<std::string> Trie::autocomplete(const std::string& prefix) {
    std::vector<std::string> result;
    TrieNode* current = root;

    // Traverse to the node corresponding to the prefix
    for (char ch : prefix) {
        ch = tolower(ch);
        if (current->children.find(ch) == current->children.end()) {
            return result; // if prefix is not found
        }
        current = current->children[ch];
    }

    // Use breadth first search to find all words under the node
    std::queue<std::pair<TrieNode*, std::string>> bfsQueue;
    bfsQueue.push({current, prefix});

    while (!bfsQueue.empty()) {
        auto currentPair = bfsQueue.front();
        bfsQueue.pop();

        TrieNode* currentNode = currentPair.first;
        std::string currentPrefix = currentPair.second;

        if (currentNode->count > 0) {
            result.push_back(currentPrefix);
        }

        for (const auto& child : currentNode->children) {
            bfsQueue.push({child.second, currentPrefix + child.first});
        }
    }

    return result;
}
