#include "trie.h"

bool validInput(std::string word){
    for (int letter : word) {
        if ( !( (letter >= 'A') && (letter <= 'Z') ) && !( (letter >= 'a') && (letter <= 'z') ) ) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]){
    std::string fileName = argv[1];
    Trie trie;

    // Read words from input text file
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open() or argc == 0) {
        std::cerr << "Error: Unable to open input file\n";
        return 1;
    }

    // Validates words before inputting into trie
    std::string word;
    while (inputFile >> word) {
        if( validInput(word) ){
            trie.insert(word);
        }else{
            std::cout << "Invalid word ' " << word << " ' contains illegal characters" << std::endl;
        }
    }
    
    // Search for a word in the trie
    std::string searchWord;
    std::cout << "> Input the word you would like to search for, or '-q' to quit: ";
    std::cin >> searchWord;

    while (searchWord != "-q") {
        // Check if search valid
        if (validInput(searchWord)) {
            auto result = trie.search(searchWord);
            if (result.first) {
                std::cout << "Word '" << searchWord << "' found. Count: " << result.second << std::endl;
            } else {
                std::cout << "Word '" << searchWord << "' not found.\n";
            }
        } else {
            std::cout << "Invalid search" << std::endl;
        }
        std::cout << "> Input the word you would like to search for, or '-q' to quit: ";
        std::cin >> searchWord;
    }

    // Generate DOT file for visualization
    trie.generateDotFile("trie_visualization.dot");

    return 0;
}
