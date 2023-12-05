#include "trie.h"

// Checks that passed character is a letter by comparing ASCII values
bool validInput(std::string word){
    for (int letter : word) {
        if ( !( (letter >= 'A') && (letter <= 'Z') ) && !( (letter >= 'a') && (letter <= 'z') ) ) {
            return false;
        }
    }
    return true;
}

void printMenu(){
    std::cout << "----------- Mode Select ------------\n";
    std::cout << "> To search for a word type in '-s'.\n";
    std::cout << "> To use autocomplete, type in '-a'.\n";
    std::cout << "> To quit the program type '-q'.\n";
    std::cout<< " > To use spellcheck , type in '-sc'. \n";
}

void wordSearch(Trie * pTrie){
    std::string searchWord;
    std::cout << "------- Database Word Search -------\n";
    std::cout << "> Input the word you would like to search for, or '-q' to quit to mode select: ";
    std::cin >> searchWord;

    while (searchWord != "-q") {
        // Check if search valid
        if (validInput(searchWord)) {
            auto result = (*pTrie).search(searchWord);
            if (result.first) {
                std::cout << "Word '" << searchWord << "' found." << "\n";;
                std::cout << "Times identical word appears in data: " << result.second << "\n";
                std::cout << "Times word is used as a prefix: " << result.third << std::endl;
            } else {
                std::cout << "Word '" << searchWord << "' not found.\n";
            }
        } else {
            std::cout << "Invalid search" << std::endl;
        }
        std::cout << "> Input the word you would like to search for, or '-q' to quit to mode select: ";
        std::cin >> searchWord;
    }
}

void wordAutocomplete(Trie * pTrie){
    std::string autoWord;
    std::cout << "-------- Word Autocomplete ---------\n";
    std::cout << "> Input part of the word you would like to attempt to auto complete, or '-q' to quit to mode select: ";
    std::cin >> autoWord;
    while (autoWord != "-q") {
        std::vector<std::string> autocompleteResults = (*pTrie).autocomplete(autoWord);
        std::cout << "Here is a list of potential words you were looking for with the given prefix of: '"
                  << autoWord << "': " << std::endl;
        // outputs words with commas between all but last
        int vecLength = autocompleteResults.size();
        for (int index = 0; index < vecLength; index++) {
            std::cout << autocompleteResults.at(index);
            if (index < vecLength - 1) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
        std::cout << "> Input part of the word you would like to attempt to auto complete, or '-q' to quit to mode select: ";
        std::cin >> autoWord;
    }
};




int main(int argc, char* argv[]){
    // Takes filename from user if it's not passed as an argument
    std::string fileName;
    if(argc > 1){
        fileName = argv[1];
    }else{
        std::cout << "> Input name of database/dictionary text file: ";
        std::cin >> fileName;
    }

    // Read words from input text file
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file\n";
        return 1;
    }

    Trie trie;
    Trie * pTrie = &trie;
    // Validates words before inputting into trie
    std::string word;
    while (inputFile >> word) {
        if( validInput(word) ){
            trie.insert(word);
        }else{
            std::cout << "Invalid word ' " << word << " ' contains illegal characters and was not included" << std::endl;
        }
    }

    // Main user input loop
    std::string mode;
    printMenu();
    std::cin >> mode;
    while(mode != "-q") {

        // Search for a word in the trie
        if (mode == "-s") { wordSearch(pTrie); }

        // Autocomplete Given Word
        if (mode == "-a") { wordAutocomplete(pTrie); }

        printMenu();
        std::cin >> mode;
    }

    // Generate DOT file for visualization
    trie.generateDotFile("trie_visualization.dot");

    std::cout << "Goodbye!" << std::endl;
    return 0;
}
