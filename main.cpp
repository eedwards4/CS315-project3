#include <iostream>

#include "BinSearchTree.hpp"
#include "TreeNode.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

// TEST SOLUTIONS
#define TEST_SIZE 28
#define TEST_MAXDEPTH 10
#define TEST_FIND 1
#define TEST_INSERT_ONE 84
#define TEST_INSERT_TWO 100

// Utils


// Tests
int testZero(BinSearchTree& tree){
    return tree.size() == TEST_SIZE;
}

int testOne(BinSearchTree& tree){
    return tree.maxDepth() == TEST_MAXDEPTH;
}

int testTwo(BinSearchTree& tree){
    return tree.find(TEST_INSERT_ONE) == TEST_FIND && tree.find(TEST_INSERT_TWO) != TEST_FIND;
}

int testThree(BinSearchTree& tree){
    return tree.iterFind(TEST_INSERT_ONE) == TEST_FIND && tree.iterFind(TEST_INSERT_TWO) != TEST_FIND;
}

void testFour(BinSearchTree& tree){
    std::cout << "Testing inorder dump...\n";
    tree.inorderDump();
    std::cout << "\n30 31 32 34 35 36 38 39 41 43 54 55 56 67 72 75 79 84 85 87 89 101 104 108 116 117 120 122" << std::endl;
    std::cout << "Test should equal the above ^\n";
}

int testFive(BinSearchTree& tree){
    tree.insert(100);
    return tree.find(100) == TEST_FIND;
}

void testSix(BinSearchTree& tree){
    std::cout << "Testing level order dump...\n";
    tree.levelOrderDump();
    std::cout << "\n" << std::endl;
    std::cout << "Test should equal the above ^\n";
}


// Main
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

    // Tests
    int testNum = 0;
    std::vector<int> testResults;
    testResults.push_back(testZero(*tree));
    testResults.push_back(testOne(*tree));
    testResults.push_back(testTwo(*tree));
    testResults.push_back(testThree(*tree));
    testFour(*tree);
    testResults.push_back(testFive(*tree));
    testSix(*tree);
    for (int i : testResults){
        if (i == 0){
            std::cout << "Test " << testNum << " failed." << std::endl;
        }
        else {
            std::cout << "Test " << testNum << " passed." << std::endl;
        }
        if (testNum == 3 || testNum == 5){
            testNum += 2;
        }
        else {
            testNum++;
        }
    }
    return 0;
}
