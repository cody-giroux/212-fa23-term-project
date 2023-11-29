#include "trie.h"

int main(int argc, char* argv[]){
    std::string fileName = argv[1];
    Trie trie;

    // Read words from input text file
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open() or argc == 0) {
        std::cerr << "Error: Unable to open input file\n";
        return 1;
    }

    std::string word;
    while (inputFile >> word) {
        trie.insert(word);
    }

    // Search for a word in the trie
    std::string searchWord;
    std::cout << "Input the word you would like to search for: " << std :: endl;
    std::cin >> searchWord;

    auto result = trie.search(searchWord);
    if (result.first) {
        std::cout << "Word '" << searchWord << "' found. Count: " << result.second << std::endl;
    } else {
        std::cout << "Word '" << searchWord << "' not found.\n";
    }

    // Generate DOT file for visualization
    trie.generateDotFile("trie_visualization.dot");

    return 0;
}
