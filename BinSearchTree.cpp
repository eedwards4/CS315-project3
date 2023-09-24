//
// Created by Ali Kooshesh on 3/1/23.
// Completed by Ethan Edwards and Emily Hernandez on 20/9/23.
//

#include "BinSearchTree.hpp"

BinSearchTree::BinSearchTree(): root{nullptr} {}

TreeNode *BinSearchTree::insert( TreeNode *root, int v ) {
    if( root == nullptr )
        return new TreeNode( v );
    if( root->value() < v )
        root->rightSubtree( insert( root->rightSubtree(), v ) );
    else
        root->leftSubtree( insert( root->leftSubtree(), v ) );
    return root;
}

void BinSearchTree::insert(int v) {
    // Insert v in the tree if it is not already a member.
    if( ! find(v) ) {
        root = insert(root, v);
    }
}

int BinSearchTree::size() {
    // Write this function first!
    return size(root);
}

int BinSearchTree::size(TreeNode *root) {
    if (root == nullptr){
        return 0;
    }

    return size(root->leftSubtree()) + size(root->rightSubtree()) + 1;

}

bool BinSearchTree::find(int v) {
    // You need to write a recursive implementation for this function.
    // Right now, it returns false so that insert can do its job.
    // That means, it will add duplicates to the tree, which is not desirable.
    return find(root, v);
}

bool BinSearchTree::find(TreeNode *root, int v) {
    if (root == nullptr){
        return false;
    }
    if (root->value() == v){
        return true;
    }
    if (root->value() < v){
        return find(root->rightSubtree(), v);
    }

    return find(root->leftSubtree(), v);

}

void BinSearchTree::iterInsert(int v){
    TreeNode *current = root;
    if (root == nullptr){root = new TreeNode(v);}
    if (iterFind(v)){return;}
    while(current != nullptr){
        if (current->value() == v){
            return;
        }
        if (current->value() < v){
            if (current->rightSubtree() == nullptr){
                current->rightSubtree(new TreeNode(v));
                return;
            }
            current = current->rightSubtree();
        }
        if (current->value() > v){
            if (current->leftSubtree() == nullptr){
                current->leftSubtree(new TreeNode(v));
                return;
            }
            current = current->leftSubtree();
        }
    }
}

bool BinSearchTree::iterFind(int v) {
    TreeNode *current = root;
    while (current != nullptr){
        if (current->value() == v){
            return true;
        }
        if (current->value() < v){
            current = current->rightSubtree();
        }
        if (current->value() > v){
            current = current->leftSubtree();
        }
    }
    return false;
}

int BinSearchTree::maxDepth() {
    return maxDepth(root);
}

int BinSearchTree::maxDepth(TreeNode *root) {
    if (root == nullptr){
        return 0;
    }
    return std::max(maxDepth(root->leftSubtree()), maxDepth(root->rightSubtree())) + 1;
}

void BinSearchTree::inorderDump() {
    inorderDump(root);
}

void BinSearchTree::inorderDump(TreeNode *root) {
    if (root == nullptr){
        return;
    }
    inorderDump(root->leftSubtree());
    std::cout << root->value() << std::endl;
    inorderDump(root->rightSubtree());
}

BinSearchTree::~BinSearchTree() {
    // This function should delete every node in the tree.
    // To do that, you will have to recursively traverse the tree, using
    // a post-order traversal.
    deleteTree(root);
}

int BinSearchTree::deleteTree(TreeNode *root) {
    if (root == nullptr){
        return 0;
    }
    TreeNode *left = root->leftSubtree();
    TreeNode *right = root->rightSubtree();
    delete root;
    return deleteTree(left) + deleteTree(right) + 1;
}
