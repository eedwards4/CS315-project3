//
// Created by Ali Kooshesh on 3/1/23.
//

#ifndef BINSEARCHTREE_BINSEARCHTREE_HPP
#define BINSEARCHTREE_BINSEARCHTREE_HPP


#include <iostream>
#include "TreeNode.hpp"

class BinSearchTree {
public:
    // Boilerplate ʕノ•ᴥ•ʔノ ︵ ┻━┻
    BinSearchTree();
    void insert( int v );
    bool find( int v );
    bool iterFind( int v );
    int size();
    void inorderDump();
    int maxDepth();
    void iterInsert( int v );

    ~BinSearchTree();

private:
    TreeNode *insert( TreeNode *, int );
    TreeNode *root;

    // Actual code
    int size(TreeNode *root);
    bool find(TreeNode *root, int v);
    int maxDepth(TreeNode *root);
    void inorderDump(TreeNode *root);

    int deleteTree(TreeNode *root);

};


#endif //BINSEARCHTREE_BINSEARCHTREE_HPP
