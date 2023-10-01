//
// Created by Ali Kooshesh on 3/1/23.
// Completed by Ethan Edwards and Emily Hernandez on 20/9/23.
//

#ifndef BINSEARCHTREE_BINSEARCHTREE_HPP
#define BINSEARCHTREE_BINSEARCHTREE_HPP


#include <iostream>
#include <vector>
#include "TreeNode.hpp"

class BinSearchTree {
public:
    // Management
    BinSearchTree();
    ~BinSearchTree();
    bool remove(int v);
    // Search methods
    int size();
    int maxDepth();
    int iterMaxDepth();
    int kthSmallest(int k);
    bool find(int v);
    bool iterFind(int v);
    bool hasRootToLeafSum(int sum);
    void inorderDump();
    void levelOrderDump();
    void valuesAtLevel(int l);
    void iterValuesAtLevel(int l);
    // Insert methods
    void insert(int v);
    void iterInsert(int v);

private:
    TreeNode *insert( TreeNode *, int );
    TreeNode *root;

    // Management
    int deleteTree(TreeNode *root);
    // Search methods
    int size(TreeNode *root);
    int maxDepth(TreeNode *root);
    bool find(TreeNode *root, int v);
    bool hasRootToLeafSum(TreeNode *root, int sum);
    void inorderDump(TreeNode *root);
    void inorderDump(TreeNode *root, std::vector<int> &values);
    void valuesAtLevel(TreeNode *root, int l, int currLvl);

};


#endif //BINSEARCHTREE_BINSEARCHTREE_HPP
