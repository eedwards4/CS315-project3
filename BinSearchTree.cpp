//
// Created by Ali Kooshesh on 3/1/23.
// Completed by Ethan Edwards on 2/10/23.
//

#include <queue>
#include <algorithm>
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

int BinSearchTree::iterMaxDepth() {
    if (root == nullptr){return 1;}
    int maxDepth = 1;
    std::queue<std::tuple<TreeNode*, int>> q;
    q.emplace(root, 1);
    while (!q.empty()){
        TreeNode *current = std::get<0>(q.front());
        int currDepth = std::get<1>(q.front());
        q.pop();
        if (currDepth > maxDepth){maxDepth = currDepth;}
        if (current->leftSubtree() != nullptr){
            q.emplace(current->leftSubtree(), currDepth+1);
        }
        if (current->rightSubtree() != nullptr){
            q.emplace(current->rightSubtree(), currDepth+1);
        }
    }
    return maxDepth;
}

int BinSearchTree::kthSmallest(int k) {
    if (k > size(root)){
        return -1;
    }
    std::vector<int> values;
    kthSmallest(root, values);
    return values.at(k-1);
}

void BinSearchTree::kthSmallest(TreeNode *root, std::vector<int> &values) { // Overload to return values as vector
    if (root == nullptr){
        return;
    }
    kthSmallest(root->leftSubtree(), values);
    values.push_back(root->value());
    kthSmallest(root->rightSubtree(), values);
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

bool BinSearchTree::hasRootToLeafSum(int sum) {
    return hasRootToLeafSum(root, sum);
}

bool BinSearchTree::hasRootToLeafSum(TreeNode *root, int sum) {
    if (root == nullptr){
        return false;
    }
    if (root->leftSubtree() == nullptr && root->rightSubtree() == nullptr){
        if (sum - root->value() < 0){return false;}
        return true;
    }
    return hasRootToLeafSum(root->leftSubtree(), sum - root->value()) || hasRootToLeafSum(root->rightSubtree(), sum - root->value());
}

bool BinSearchTree::areIdentical(BinSearchTree *bst) {
    return areIdentical(root, bst->root);
}

bool BinSearchTree::areIdentical(TreeNode *root1, TreeNode *root2) {
    if (root1 == nullptr && root2 == nullptr){
        return true;
    }
    if (root1 == nullptr || root2 == nullptr){
        return false;
    }
    if (root1->value() != root2->value()){
        return false;
    }
    return areIdentical(root1->leftSubtree(), root2->leftSubtree()) && areIdentical(root1->rightSubtree(), root2->rightSubtree());
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

void BinSearchTree::valuesAtLevel(int l) {
    valuesAtLevel(root, l, 1);
}

void BinSearchTree::valuesAtLevel(TreeNode *root, int l, int currLvl){
    if (root == nullptr){
        return;
    }
    if (l == currLvl){
        std::cout << root->value() << " ";
        return;
    }
    valuesAtLevel(root->leftSubtree(), l, currLvl+1);
    valuesAtLevel(root->rightSubtree(), l, currLvl+1);
}


void BinSearchTree::iterValuesAtLevel(int l) {
    if (root == nullptr){
        return;
    }
    std::queue<std::tuple<TreeNode*, int>> q;
    q.emplace(root, 1);
    while (!q.empty()){
        TreeNode *current = std::get<0>(q.front());
        int currLvl = std::get<1>(q.front());
        q.pop();
        if (currLvl == l){
            std::cout << current->value() << " ";
        }
        else {
            if (current->leftSubtree() != nullptr) {
                q.emplace(current->leftSubtree(), currLvl + 1);
            }
            if (current->rightSubtree() != nullptr) {
                q.emplace(current->rightSubtree(), currLvl + 1);
            }
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

// New Trees
// Helpers
void BinSearchTree::makeInorderVector(TreeNode *root, std::vector<int> &values) { // Yes this is a duplicate of the kthSmallest overload. Why? Clarity.
    if (root == nullptr){
        return;
    }
    makeInorderVector(root->leftSubtree(), values);
    values.push_back(root->value());
    makeInorderVector(root->rightSubtree(), values);
}

TreeNode *BinSearchTree::makeBalancedTreeNode(std::vector<int> &values, int start, int end) {
    if (start > end){
        return nullptr;
    }
    int mid = (start + end) / 2;
    TreeNode *nNode = new TreeNode(values.at(mid));
    nNode->leftSubtree(makeBalancedTreeNode(values, start, mid-1));
    nNode->rightSubtree(makeBalancedTreeNode(values, mid+1, end));
    return nNode;
}

BinSearchTree *BinSearchTree::makeBalancedTree(std::vector<int> &values, int start, int end) {
    BinSearchTree *balancedTree = new BinSearchTree();
    balancedTree->root = makeBalancedTreeNode(values, start, end);
    return balancedTree;
}

void pareDupes(std::vector<int> &v){
    int i = 0;
    while (i < v.size()-1){
        if (v.at(i) == v.at(i+1)){
            v.erase(v.begin()+(i+1));
        }
        else{
            i++;
        }
    }
}

// Main functions
BinSearchTree *BinSearchTree::intersectWith(BinSearchTree *bst) {
    BinSearchTree *intersection;
    std::vector<int> thisValues, otherValues, intersectionValues;
    makeInorderVector(root, thisValues);
    makeInorderVector(bst->root, otherValues);
    int i = 0, j = 0;
    while (i < thisValues.size() && j < otherValues.size()){ // Get values
        if (thisValues.at(i) == otherValues.at(j)){
            intersectionValues.push_back(thisValues.at(i));
            i++;
            j++;
        }
        else if (thisValues.at(i) < otherValues.at(j)){
            i++;
        }
        else {
            j++;
        }
    }
    // Make balanced tree from values
    std::sort(intersectionValues.begin(), intersectionValues.end());
    intersection = makeBalancedTree(intersectionValues, 0, intersectionValues.size()-1);
    return intersection;
}

BinSearchTree *BinSearchTree::unionWith(BinSearchTree *bst) {
    BinSearchTree *unionTree;
    std::vector<int> thisValues, otherValues, unionValues;
    makeInorderVector(root, thisValues);
    makeInorderVector(bst->root, otherValues);
    int i = 0, j = 0;
    while (i < thisValues.size() && j < otherValues.size()){ // Get values
        if (thisValues.at(i) != otherValues.at(j)){
            unionValues.push_back(thisValues.at(i));
            unionValues.push_back(otherValues.at(j));
        }
        else{
            unionValues.push_back(thisValues.at(i));
        }
        i++;
        j++;
    }
    while (i < thisValues.size()){ // Add remaining values for i
        unionValues.push_back(thisValues.at(i));
        i++;
    }
    while (j < otherValues.size()){ // Add remaining values for j
        unionValues.push_back(otherValues.at(j));
        j++;
    }
    // Make balanced tree from values
    std::sort(unionValues.begin(), unionValues.end());
    pareDupes(unionValues);
    unionTree = makeBalancedTree(unionValues, 0, unionValues.size()-1);
    return unionTree;
}

BinSearchTree *BinSearchTree::differenceOf(BinSearchTree *bst) {
    BinSearchTree *differenceTree;
    std::vector<int> thisValues, otherValues, differenceValues;
    makeInorderVector(root, thisValues);
    makeInorderVector(bst->root, otherValues);
    int i = 0, j = 0;
    while (i < thisValues.size()){ // Get values
        if (!bst->find(thisValues.at(i))){
            differenceValues.push_back(thisValues.at(i));
        }
        i++;
    }
    while (j < otherValues.size()){ // Get values
        if (!this->find(otherValues.at(j))){
            differenceValues.push_back(otherValues.at(j));
        }
        j++;
    }
    // Make balanced tree from values
    std::sort(differenceValues.begin(), differenceValues.end());
    differenceTree = makeBalancedTree(differenceValues, 0, differenceValues.size()-1);
    return differenceTree;
}
