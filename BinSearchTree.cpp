//
// Created by Ali Kooshesh on 3/1/23.
// Completed by Ethan Edwards and Emily Hernandez on 20/9/23.
//

#include <queue>
#include "BinSearchTree.hpp"

// Management
BinSearchTree::BinSearchTree(): root{nullptr} {}

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

void restructureFromPoint(TreeNode *root, BinSearchTree *tree){ // Restructure tree from a given node. Assumes that the node has been severed from the tree, but NOT DELETED.
    std::queue<TreeNode*> q, finalQ;
    q.push(root->leftSubtree());
    q.push(root->rightSubtree());
    while (!q.empty()){ // Add all nodes in subtree to queue
        TreeNode *current = q.front();
        finalQ.push(current);
        q.pop();
        if (current->leftSubtree() != nullptr){
            q.push(current->leftSubtree());
        }
        if (current->rightSubtree() != nullptr){
            q.push(current->rightSubtree());
        }
    }
    while (!finalQ.empty()){ // Reinsert nodes in main tree
        TreeNode *current = finalQ.front();
        tree->insert(current->value());
        finalQ.pop();
    }
}

bool BinSearchTree::remove(int v) {
    TreeNode *item = root, *parent = nullptr;
    while (item != nullptr){ // Find item
        if (item->value() == v){break;}
        parent = item;
        if (item->value() < v){item = item->rightSubtree();}
        else {item = item->leftSubtree();}
    }
    if (item == nullptr){return false;} // Return false if we can't find the item

    // Delete item
    if (item->leftSubtree() == nullptr && item->rightSubtree() == nullptr){ // Leaf node, sever from tree
        if (parent->leftSubtree() == item){parent->leftSubtree(nullptr);}
        else {parent->rightSubtree(nullptr);}
    }
    else if (item->rightSubtree() == nullptr){ // Only left child, splice subtree to parent
        if (parent->leftSubtree() == item){parent->leftSubtree(item->leftSubtree());}
        else {parent->rightSubtree(item->leftSubtree());}
    }
    else if (item->leftSubtree() == nullptr){ // Only right child, splice subtree to parent
        if (parent->leftSubtree() == item){parent->leftSubtree(item->rightSubtree());}
        else {parent->rightSubtree(item->rightSubtree());}
    }
    else{ // Two children, restructure tree
        // Sever node+subtree from tree
        if (parent->leftSubtree() == item){parent->leftSubtree(nullptr);}
        else {parent->rightSubtree(nullptr);}
        restructureFromPoint(item, this); // Reinsert subtree into tree
    }
    delete item;
    return true;
}

// Search methods
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

int BinSearchTree::maxDepth() {
    return maxDepth(root);
}

int BinSearchTree::maxDepth(TreeNode *root) {
    if (root == nullptr){
        return 0;
    }
    return std::max(maxDepth(root->leftSubtree()), maxDepth(root->rightSubtree())) + 1;
}

bool BinSearchTree::find(int v) {
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

void BinSearchTree::inorderDump() {
    inorderDump(root);
}

void BinSearchTree::inorderDump(TreeNode *root) {
    if (root == nullptr){
        return;
    }
    inorderDump(root->leftSubtree());
    std::cout << root->value() << " ";
    inorderDump(root->rightSubtree());
}

void BinSearchTree::levelOrderDump() {
    if (root == nullptr){
        return;
    }
    std::queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()){
        TreeNode *current = q.front();
        std::cout << current->value() << " ";
        q.pop();
        if (current->leftSubtree() != nullptr){
            q.push(current->leftSubtree());
        }
        if (current->rightSubtree() != nullptr){
            q.push(current->rightSubtree());
        }
    }
}

// Insert methods
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
