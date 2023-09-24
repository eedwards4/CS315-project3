//
// Created by Ali Kooshesh on 3/1/23.
// Completed by Ethan Edwards and Emily Hernandez on 20/9/23.
//

#ifndef BINSEARCHTREE_BINSEARCHTREE_HPP
#define BINSEARCHTREE_BINSEARCHTREE_HPP


#include <iostream>
#include "TreeNode.hpp"

class BinSearchTree {
public:
    // Management
    BinSearchTree();
    ~BinSearchTree();

    // Search methods
    int size();
    int maxDepth();
    bool find( int v );
    bool iterFind( int v );
    void inorderDump();
    void levelOrderDump();
    // Insert methods
    void insert( int v );
    void iterInsert( int v );

private:
    TreeNode *insert( TreeNode *, int );
    TreeNode *root;

    // Search methods
    int size(TreeNode *root);
    int maxDepth(TreeNode *root);
    bool find(TreeNode *root, int v);
    void inorderDump(TreeNode *root);
    // Management
    int deleteTree(TreeNode *root);

};


#endif //BINSEARCHTREE_BINSEARCHTREE_HPP
