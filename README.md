# 212 Fa23 Term Project
Group 27 for the CSC 212 Term Project

## Topic: [Trie](https://en.wikipedia.org/wiki/Trie)
Focus: Storing and searching through a dictionary of words

## Members:
Skye Vrucak  (VioletVex)

David Ajuhan  (dajuhan)

Sahil Chadha  (schadha009)

Cody Giroux  (cody-giroux)

## Description
Program relying on a trie data structure to look up words in a database and/or autcomplete words using a provided dictionary.
Dictionary file 'popular.txt' was acquired from [this repository](https://github.com/dwyl/english-words)
The only edits made to popular.txt was the removal of certain words..

## Compile and Use Instructions
No prior dependencies needed. Can be compiled using an up-to-date g++ compiler.
One command line argument (optional): name of text file containing dictionary of words.
File name can also be inputted after the program runs if it's not passed in as an argument.
```
g++ main.cpp trie.cpp -o 'executable name'
./'executable name' 'text file name' 
```
Format of the file is simply one complete word per line of text file.
Words must contain just letters, any line with numbers, spaces, or other characters will not be included.

If you want to use the program to look up words in the text file, add your own file.
If you want to use autocomplete, you can use the included 'popular.txt' file as a dictionary.
