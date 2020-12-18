#include "BinaryTree.h"

#include <iostream>
using namespace std;

BinaryTree::~BinaryTree()
{
    delete root;
}

void BinaryTree::clear()
{
    delete root;
    root = nullptr;
}

void BinaryTree::insert(int key, int value)
{
    Node* prev = nullptr;
    Node* current = root;

    while (current)
    {
        prev = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    Node* newNode = new Node(prev, key, value);

    if (prev == nullptr)
    {
        root = newNode;
    }
    else
    {
        if (key < prev->key)
            prev->left = newNode;
        else
            prev->right = newNode;
    }
}


bool BinaryTree::find(int key, int& value)
{
    bool isFound = false;
    Node* n = find(key);

    value = n->value;
    isFound = n->key == key;

    return isFound;
}

BinaryTree::Node* BinaryTree::find(int key)
{
    Node* prev = nullptr;
    Node* current = root;

    while (current)
    {
        if (current->key == key)
        {
            return current;
        }

        prev = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    return prev;
}

void BinaryTree::inorder()
{
    inorder(root);
}

void BinaryTree::preorder()
{
    preorder(root);
}

void BinaryTree::postorder()
{
    postorder(root);
}

void BinaryTree::inorder(Node* node)
{
    if (node)
    {
        inorder(node->left);
        cout << node->key << ' ';
        inorder(node->right);
    }
}

void BinaryTree::preorder(Node* node)
{
    if (node)
    {
        cout << node->key << ' ';
        preorder(node->left);
        preorder(node->right);
    }
}

void BinaryTree::postorder(Node* node)
{
    if (node)
    {
        postorder(node->left);
        postorder(node->right);
        cout << node->key << ' ';
    }
}

int BinaryTree::min()
{
    Node* n = min(root);
    if (n)
        return n->key;
    else
        return -1;
}

int BinaryTree::max()
{
    Node* n = max(root);
    if (n)
        return n->key;
    else
        return -1;
}

BinaryTree::Node* BinaryTree::min(Node* node)
{
    Node* prev = nullptr;
    Node* current = node;

    while (current)
    {
        prev = current;
        current = current->left;
    }

    return prev;
}

BinaryTree::Node* BinaryTree::max(Node* node)
{
    Node* prev = nullptr;
    Node* current = node;

    while (current)
    {
        prev = current;
        current = current->right;
    }

    return prev;
}

int BinaryTree::morekey(int key)
{
    Node* n = find(key);

    if (n->key >= key)
        return n->key;
    else
        return -1;
}

int BinaryTree::lesskey(int key)
{
    Node* n = find(key);

    if (n->key <= key)
        return n->key;
    else
        return -1;
}

int BinaryTree::size()
{
    return size(root);
}

int BinaryTree::size(Node* node)
{
    if (node == nullptr)
        return 0;
    return size(node->left) + size(node->right) + 1;
}

void BinaryTree::transplant(Node* current, Node* replacing)
{
    if (current->parent == nullptr) //current is root
    {
        root = replacing;
    }
    else
    {
        if (current == current->parent->left)
            current->parent->left = replacing;
        else
            current->parent->right = replacing;
    }
    if (replacing != nullptr)
        replacing->parent = current->parent;
}

void BinaryTree::erase(int key)
{
    Node* del = find(key);
    if (del->key != key)
        return;

    if (del->left == nullptr)
        transplant(del, del->right);
    else if (del->right == nullptr)
            transplant(del, del->left);
        else   
        {
            Node* nextmin = min(del->right);

            if (nextmin->parent != del) //it is not a child
            {
             transplant(nextmin, nextmin->right);
                nextmin->right = del->right;
                del->right->parent = nextmin;
            }

            transplant(del, nextmin);

            nextmin->left = del->left;
            del->left->parent = nextmin;
        }
    
    del->destroy();
}