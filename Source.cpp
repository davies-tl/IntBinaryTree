/*
Program name: IntBinaryTreeClass.cpp
Programmer: Tyler Davies
Date: 11-21-21
Version: 2.0
Description: This program contains a class called IntBinaryTree, which creates a binary tree of integers.
             The class has public member functions for inserting, searching for, removing, and displaying
             its nodes; along with ones to display the whole tree. These functions call private recursive
             supporter functions. Version 2.0 adds two counting functions to the class; one to count
             total nodes, and one to count leaves. The main function tests the class's counting functions.
*/

#include<iostream>
using namespace std;

//The IntBinaryTree class creates a TreeNode structure to hold an integer and two TreeNode pointers
//for its subtrees. The class also creates a TreeNode pointer for the first node.
class IntBinaryTree
{
private:
    struct TreeNode
    {
        int number;
        TreeNode* left, * right;
    };
    TreeNode* root;
    void insert(TreeNode*&, TreeNode*&);
    void deleteNode(int, TreeNode*&);
    void makeDeletion(TreeNode*&);
    void inOrder(TreeNode*) const;
    void preOrder(TreeNode*) const;
    void postOrder(TreeNode*) const;
    void countNode(int&, TreeNode*);
    void countLeaf(int&, TreeNode*);
    void destroySubTree(TreeNode*);
public:
    IntBinaryTree()    //Constructor
    {
        root = nullptr;
    }
    void insertNode(int);
    bool searchNode(int);
    void remove(int num)    //Calls deleteNode, passing num and root as the starting position.
    {
        deleteNode(num, root);
    }
    void displayInOrder() const    //Calls inOrder and passes root as the starting position.
    {
        inOrder(root);
    }
    void displayPreOrder() const    //Calls preOrder and passes root as the starting position.
    {
        preOrder(root);
    }
    void displayPostOrder() const    //Calls postOrder and passes root as the starting position.
    {
        postOrder(root);
    }
    int countTreeNodes();
    int countTreeLeaves();
    ~IntBinaryTree()    //Destructor
    {
        destroySubTree(root);
    }
};

//The insertNode function dynamically creates a TreeNode object called newNode, assigning num to its
//number and setting its subtree pointers to NULL. It then calls insert, passing the newNode and root.
void IntBinaryTree::insertNode(int num)
{
    TreeNode* newNode;
    newNode = new TreeNode;
    newNode->number = num;
    newNode->left = newNode->right = NULL;
    insert(newNode, root);
}

//The insert function will place a newNode in the tree when the nodePtr is NULL; otherwise, it
//finds the appropriate location in the tree, then places the newNode. It is recursive.
void IntBinaryTree::insert(TreeNode*& newNode, TreeNode*& nodePtr)
{
    if (nodePtr == NULL)
        nodePtr = newNode;
    else if (newNode->number < nodePtr->number)
        insert(newNode, nodePtr->left);
    else
        insert(newNode, nodePtr->right);
}

//The searchNode function traverses the tree checking if each node's number is equal to num. It
//returns true if num is found in the tree, otherwise it returns false.
bool IntBinaryTree::searchNode(int num)
{
    TreeNode* nodePtr;
    nodePtr = root;
    while (nodePtr)
    {
        if (num == nodePtr->number)
            return true;
        else if (num < nodePtr->number)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }
    return false;
}

//The deleteNode function compares the current node's number with num and calls the makeDeletion
//function when found, passing the current node as its argument. It is recursive.
void IntBinaryTree::deleteNode(int num, TreeNode*& nodePtr)
{
    if (num < nodePtr->number)
        deleteNode(num, nodePtr->left);
    else if (num > nodePtr->number)
        deleteNode(num, nodePtr->right);
    else
        makeDeletion(nodePtr);
}

//The makeDeletion function deletes a node, then reattaches its child nodes to the tree.
void IntBinaryTree::makeDeletion(TreeNode*& nodePtr)
{
    TreeNode* temp;
    if (nodePtr == NULL)
        cout << "Error: cannot delete an empty node.\n";
    else if (nodePtr->left == NULL)
    {
        temp = nodePtr;
        nodePtr = nodePtr->right;
        delete temp;
    }
    else if (nodePtr->right == NULL)
    {
        temp = nodePtr;
        nodePtr = nodePtr->left;
        delete temp;
    }
    else
    {
        temp = nodePtr->right;
        while (temp->left)
            temp = temp->left;
        temp->left = nodePtr->left;
        temp = nodePtr;
        nodePtr = nodePtr->right;
        delete temp;
    }
}

//The inOrder function displays all nodes in order; it is recursive.
void IntBinaryTree::inOrder(TreeNode* nodePtr) const
{
    if (nodePtr)
    {
        inOrder(nodePtr->left);
        cout << nodePtr->number << endl;
        inOrder(nodePtr->right);
    }
}

//The preOrder function displays all nodes pre-order; it is recursive.
void IntBinaryTree::preOrder(TreeNode* nodePtr) const
{
    if (nodePtr)
    {
        cout << nodePtr->number << endl;
        preOrder(nodePtr->left);
        preOrder(nodePtr->right);
    }
}

//The postOrder function displays all nodes post-order; it is recursive.
void IntBinaryTree::postOrder(TreeNode* nodePtr) const
{
    if (nodePtr)
    {
        postOrder(nodePtr->left);
        postOrder(nodePtr->right);
        cout << nodePtr->number << endl;
    }
}

//The countTreeNodes function initializes a counting variable, passes it with root as the starting
//position to countNode, and afterwards returns the variable which represents the total nodes.
int IntBinaryTree::countTreeNodes()
{
    int numNodes = 0;
    countNode(numNodes, root);
    return numNodes;
}

//The countNode function counts a node then calls itself, passing its left and right subtrees. It
//is recursive.
void IntBinaryTree::countNode(int& count, TreeNode* nodePtr)
{
    if (nodePtr)
    {
        count += 1;
        countNode(count, nodePtr->left);
        countNode(count, nodePtr->right);
    }
}

//The countTreeLeaves function initializes a counting variable, passes it with root as the starting
//position to countLeaf, and afterwards returns the variable which represents the total leaf nodes.
int IntBinaryTree::countTreeLeaves()
{
    int numLeaves = 0;
    countLeaf(numLeaves, root);
    return numLeaves;
}

//The countLeaf function counts a node if it has no child nodes. Otherwise, it calls itself,
//passing its left and right subtrees. It is recursive.
void IntBinaryTree::countLeaf(int& count, TreeNode* nodePtr)
{
    if (nodePtr)
    {
        if (nodePtr->left == NULL && nodePtr->right == NULL)
            count += 1;
        countLeaf(count, nodePtr->left);
        countLeaf(count, nodePtr->right);
    }
}

//The destroySubTree function is called by the destructor, and deletes all of the nodes in a tree.
//It is recursive.
void IntBinaryTree::destroySubTree(TreeNode* nodePtr)
{
    if (nodePtr)
    {
        if (nodePtr->left)
            destroySubTree(nodePtr->left);
        if (nodePtr->right)
            destroySubTree(nodePtr->right);
        delete nodePtr;
    }
}

//The main function acts as a driver program. It creates a IntBinaryTree object, inserts numbers in
//the tree, and tests its countTreeNodes and countTreeLeaves functions.
int main()
{
    IntBinaryTree tree;
    int count;

    cout << "Inserting nine (9) nodes into the tree.\nValues: 10, 15, 8, 22, 13, 9, 5, 30, and 2\n\n";
    cout << "Visual Representation of Tree:\n      10\n    8    15\n  5  9 13  22\n2            30\n\n";
    tree.insertNode(10);
    tree.insertNode(15);
    tree.insertNode(8);
    tree.insertNode(22);
    tree.insertNode(13);
    tree.insertNode(9);
    tree.insertNode(5);
    tree.insertNode(30);
    tree.insertNode(2);

    count = tree.countTreeNodes();
    cout << "The tree has " << count << " total nodes.\n";

    count = tree.countTreeLeaves();
    cout << "The tree has " << count << " leaf nodes.\n";

    exit(0);
}