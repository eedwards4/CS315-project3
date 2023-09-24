#include <iostream>

#include "BinSearchTree.hpp"
#include "TreeNode.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

int main( int argc, char *argv[] ) {
    // create a tree and then print the values of its nodes
    // from the smallest to the largest.

    if( argc != 2 ) {
        std::cout << "usage: executable name-of-input-file\n";
        exit(5);
    }
    std::fstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if(!inputStream.is_open()) {
        std::cout << "Unable to open the input file " <<
                  argv[1] << std::endl;
        std::cout << "Terminating...\n";
        exit(7);
    }


    BinSearchTree *tree = new BinSearchTree();
    int aValue;
    while( inputStream >> aValue ) {
        tree->insert(aValue);
    }

    // size has not been implemented. It currently returns zero
    // just so that the program compiles. You should write
    // an implementation for size first. Then, write an implementation for
    // find.
    std::cout << tree->size() << std::endl;
    std::cout << tree->maxDepth() << std::endl;
    std::cout << tree->iterFind(84) << std::endl;
    tree->inorderDump();
    tree->iterInsert(100);
    tree->inorderDump();
    tree->~BinSearchTree();
    return 0;
}
