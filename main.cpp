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
BinSearchTree* treeBuilder(std::string fName){
    std::fstream inputStream;
    inputStream.open(fName, std::ios::in);
    if(!inputStream.is_open()) {
        std::cout << "Unable to open the input file " << fName << std::endl;
        std::cout << "Terminating...\n";
        exit(7);
    }

    BinSearchTree *tree = new BinSearchTree();
    int aValue;
    while( inputStream >> aValue ) {
        tree->insert(aValue);
    }
    return tree;
}

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
    std::cout << "\n36 32 104 30 35 89 120 31 34 43 101 117 122 41 79 108 39 54 85 116 38 56 84 87 55 75 67 72" << std::endl;
    std::cout << "Test should equal the above ^\n";
}

std::vector<int> testSeven(BinSearchTree& tree){
    std::vector<int> tests;
    std::vector<int> testIntsTrue = {34, 38, 101};
    std::vector<int> testIntsFalse = {100, 200, 300};
    for (int i : testIntsTrue){ // These should all be true
        tests.push_back(tree.remove(i) && !tree.find(i));
    }
    for (int i : testIntsFalse){ // These should all be false
        tests.push_back(!tree.remove(i) && !tree.find(i));
    }
    return tests;
}

std::vector<int> testEight(BinSearchTree& tree){
    std::vector<int> tests;
    std::vector<int> testInts = {4, 8, 10, 20, 11, 9};
    std::vector<int> answerInts = {34, 39, 43, 87, 54, 41};
    for (int i = 0; i < testInts.size(); i++){
        int tmp = tree.kthSmallest(testInts.at(i));
        if (tmp != answerInts.at(i)){
            tests.push_back(0);
        }
        else {
            tests.push_back(1);
        }
    }
    return tests;
}

void testNine(BinSearchTree& tree){
    std::cout << "Testing values at level [3]:\n";
    tree.valuesAtLevel(3);
    std::cout << "\n30 35 89 120" << std::endl;
    std::cout << "Test should equal the above ^\n";

    std::cout << "Testing values at level [4]:\n";
    tree.valuesAtLevel(4);
    std::cout << "\n31 34 43 101 117 122" << std::endl;
    std::cout << "Test should equal the above ^\n";

    std::cout << "Testing values at level [8]:\n";
    tree.valuesAtLevel(8);
    std::cout << "\n55 75" << std::endl;
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
    std::string fName = argv[1];

    BinSearchTree *tree = treeBuilder(fName);

    // Tests
    int testNum = 0;
    std::vector<int> testResults;
    std::vector<std::vector<int>> multiTestResults;
    testResults.push_back(testZero(*tree));
    testResults.push_back(testOne(*tree));
    testResults.push_back(testTwo(*tree));
    testResults.push_back(testThree(*tree));
    testFour(*tree);
    testResults.push_back(testFive(*tree));
    tree = treeBuilder(fName);
    testSix(*tree);
    std::cout << "Running simple tests...\n";
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
    std::cout << "Running multi tests...\n";
    multiTestResults.push_back(testSeven(*tree));
    tree = treeBuilder(fName);
    multiTestResults.push_back(testEight(*tree));
    testNine(*tree);
    int iter = 7;
    for (std::vector<int> i : multiTestResults){
        std::cout << "Results for test " << iter << ":" << std::endl;
        for (int j = 0; j < i.size(); j++){
            if (i.at(j) == 0){std::cout << "FAILED TEST: " << j << std::endl;}
            else {std::cout << "OK" << std::endl;}
        }
        iter++;
    }
    return 0;
}
