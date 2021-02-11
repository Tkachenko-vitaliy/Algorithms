#include "AVLTree.h"

#include <assert.h>
#include <iostream>

AVLTree::Node* AVLTree::rotateLeftSmall(Node* node)
{
    Node* pivot = node->right;
    node->right = pivot->left;
    pivot->left = node;

    if (pivot->balance == 1 || pivot->balance == -1)
    {
        pivot->balance = 0; 
        node->balance = 0;
    }
    else
    {
        pivot->balance = -1;
        node->balance = 1;
    }
    return pivot;
}

AVLTree::Node* AVLTree::rotateRightSmall(Node* node)
{
    Node* pivot = node->left;
    node->left = pivot->right;
    pivot->right = node;

    if (pivot->balance == 1 || pivot->balance == -1)
    {
        pivot->balance = 0;
        node->balance = 0;
    }
    else
    {
        pivot->balance = 1;
        node->balance = -1;
    }

    return pivot;
}

AVLTree::Node* AVLTree::rotateLeftBig(Node* node)
{
    Node* pivot = node->right;
    Node* bottom = pivot->left;
    Node* pivotLeftChild = pivot->left;

    pivot->left = pivotLeftChild->right;
    node->right = pivotLeftChild->left;
    pivotLeftChild->left = node;
    pivotLeftChild->right = pivot;

    pivotLeftChild->balance = 0;

    switch (bottom->balance)
    {
    case 0:
        node->balance = 0;
        pivot->balance = 0;
        break;
    case 1:
        node->balance = -1;
        pivot->balance = 0;
        break;
    case -1:
        node->balance = 0;
        pivot->balance = 1;
    default:
        assert(false); //Wrong balance?
        break;
    }

    return pivotLeftChild;
}

AVLTree::Node* AVLTree::rotateRightBig(Node* node)
{
    Node* pivot = node->left;
    Node* bottom = pivot->right;
    Node* pivotRightChild = pivot->right;

    pivot->right = pivotRightChild->left;
    node->left = pivotRightChild->right;
    pivotRightChild->left = pivot;
    pivotRightChild->right = node;

    switch (bottom->balance)
    {
    case 0:
        node->balance = 0;
        pivot->balance = 0;
        pivotRightChild->balance = 0;
        break;
    case 1:
        node->balance = 0;
        pivot->balance = -1;
        pivotRightChild->balance = 0;
        break;
    case -1:
        node->balance = 1;
        pivot->balance = 0;
        pivotRightChild->balance = 0;
        break;
    default:
        assert(false); //Wrong balance?
        break;
    }

    return pivotRightChild;
}

void AVLTree::insert(int key, int value)
{
    bool heightChanged = false;
    root = insert(root, key, value, heightChanged);
}

AVLTree::Node* AVLTree::insert(Node* node, int key, int value, bool& heightChanged)
{
    if (node == nullptr)
    {
        heightChanged = true;
        return new Node(key, value);
    }

    balance_t offset = 0;

    if (key < node->key)
    {
        node->left = insert(node->left, key, value, heightChanged);
        if (heightChanged)
        {
            offset = -1;
        }
    }
    else
    {
        node->right = insert(node->right, key, value, heightChanged);
        if (heightChanged)
        {
            offset = 1;
        }
    }

    return checkBalance(node, offset, heightChanged);
}

AVLTree::Node* AVLTree::checkBalance(Node* node, balance_t offset, bool& heightChanged)
{
    if (offset == 0)
    {
        return node;
    }

    node->balance += offset;

    switch (node->balance)
    {
    case 0:
        heightChanged = false;
    case -1:
    case 1:
        break;
    case -2:
        node->balance++;
        node = rebalance(node, offset, heightChanged);
        break;
    case 2:
        node->balance--;
        node = rebalance(node, offset, heightChanged);
        break;
    default:
        assert(false);
        break;
    }

    return node;
}

AVLTree::Node* AVLTree::rebalance(Node* node, balance_t newBalance, bool& heightChanged)
{
    if (newBalance < 0) //left branch
    {
        Node* left = node->left;
        if (left->balance == -1) //left child sub-tree is higher then right
        {
            node = rotateRightSmall(node);
        }
        else
        {
            node = rotateRightBig(node);
        }
    }
    else //right branch
    {
        Node* right = node->right;
        if (right->balance == 1) //right child sub-tree is higher then left
        {
            node = rotateLeftSmall(node);
        }
        else
        {
            node = rotateLeftBig(node);
        }
    }

    heightChanged = node->balance != 0;

    return node;
}


size_t  AVLTree::getHeightLeft()
{
    if (root == nullptr)
    {
        return 0;
    }

    size_t height = 0;

    Node* node = root->left;
    while (node)
    {
        height++;
        node = node->left;
    }
    return height;
}

size_t AVLTree::getHeightRight()
{
    if (root == nullptr)
    {
        return 0;
    }

    size_t height = 0;

    Node* node = root->right;
    while (node)
    {
        height++;
        node = node->right;
    }
    return height;
}

void AVLTree::output(bool showBalance)
{
    output(root, showBalance, 1);
}

void AVLTree::output(Node* node, bool showBalance, unsigned int level)
{
    if (node)
    {
        output(node->right, showBalance, level + 1);
        for (unsigned int i = 1; i <= level; i++) 
            std::cout << "   ";
        std::cout << node->key;
        if (showBalance)
            std::cout << '(' << (int)node->balance << ')';
        std::cout << std::endl;
        output(node->left, showBalance, level+1);
    }
}