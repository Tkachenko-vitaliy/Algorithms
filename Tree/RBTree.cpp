#include "RBTree.h"

#include <iostream>

using namespace std;

RBTree::~RBTree()
{
    clear();
}

void RBTree::rotateLeft(Node* node)
{
    Node* nodeNext = node->right;
    node->right = nodeNext->left;

    if (nodeNext->left != &nil)
        nodeNext->left->parent = node;

    nodeNext->parent = node->parent;

    if (node->parent == &nil)
        root = nodeNext;
    else if (node == node->parent->left) //node is the left child
        node->parent->left = nodeNext;
    else node->parent->right = nodeNext;

    nodeNext->left = node;
    node->parent = nodeNext;
}

void RBTree::rotateRight(Node* node)
{
    Node* nodeNext = node->left;
    node->left = nodeNext->right;

    if (nodeNext->right != &nil)
        nodeNext->right->parent = node;

    nodeNext->parent = node->parent;

    if (node->parent == &nil)
        root = nodeNext;
    else if (node == node->parent->left) //node is the left child
        node->parent->left = nodeNext;
    else node->parent->right = nodeNext;

    nodeNext->right = node;
    node->parent = nodeNext;
}

void RBTree::insert(int key, int value)
{
    Node* prev = &nil;
    Node* current = root;

    while (current !=&nil)
    {
        prev = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    Node* newNode = new Node(prev, key, value);

    if (prev == &nil)
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

    newNode->left = &nil;
    newNode->right = &nil;
    newNode->color = Node::RED;

    InsertFixUp(newNode);
}

void RBTree::InsertFixUp(Node* node)
{
    while (node->parent->color == Node::RED)
    {
        if (node->parent == node->parent->parent->left) //the parent of our node is the left child
        {
            Node* uncle = node->parent->parent->right;
            if (node->color == Node::RED) // Both left and right under current node are red
            {
                node->parent->color = Node::BLACK;
                uncle->color = Node::BLACK;
                node->parent->parent->color = Node::RED;
                node = node->parent->parent;
            }
            else
            {
                if (node->parent->right == node) //the node is right child
                {
                    node = node->parent;
                    rotateLeft(node);
                }
                node->parent->color = Node::BLACK;
                node->parent->parent->color = Node::RED;
                rotateRight(node);
            }
        }
        else
        {
            Node* uncle = node->parent->parent->left;
            if (node->color == Node::RED) // Both left and right under current node are red
            {
                node->parent->color = Node::BLACK;
                uncle->color = Node::BLACK;
                node->parent->parent->color = Node::RED;
                node = node->parent->parent;
            }
            else
            {
                if (node->parent->left == node) //the node is left child
                {
                    node = node->parent;
                    rotateRight(node);
                }
                node->parent->color = Node::BLACK;
                node->parent->parent->color = Node::RED;
                rotateLeft(node);
            }
        }
    }

    root->color = Node::BLACK;
}

void RBTree::inorder()
{
    inorder(root);
}

void RBTree::inorder(Node* node)
{
    if (node)
    {
        inorder(node->left);
        if (node!=&nil)
            cout << node->key << ' ';
        inorder(node->right);
    }
}

bool RBTree::find(int key, int& value)
{
    bool isFound = false;
    Node* n = find(key);

    value = n->value;
    isFound = n->key == key;

    return isFound;
}

RBTree::Node* RBTree::find(int key)
{
    Node* prev = nullptr;
    Node* current = root;

    while (current != &nil)
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

RBTree::Node* RBTree::min(Node* node)
{
    Node* prev = nullptr;
    Node* current = node;

    while (current != &nil)
    {
        prev = current;
        current = current->left;
    }

    return prev;
}

RBTree::Node* RBTree::max(Node* node)
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


void RBTree::erase(int key)
{
    Node* del = find(key);
    if (del->key != key)
        return;

    Node::Color originalColor = del->color;
    Node* moving = nullptr;

    if (del->left == &nil) {
        moving = del->right;
        transplant(del, del->right);
    }
    else if (del->right == &nil) {
            moving = del->left;
            transplant(del, del->left);
        }
    else
    {
        Node* nextmin = min(del->right);
        originalColor = nextmin->color;
        moving = nextmin->right;

        if (nextmin->parent == del) //nextmin is a child
        {
            moving->parent = nextmin;
        }
        else
        {
            transplant(nextmin, nextmin->right);
            nextmin->right = del->right;
            nextmin->right->parent = nextmin;
        }

        transplant(del, nextmin);

        nextmin->left = del->left;
        nextmin->left->parent = nextmin;
        nextmin->color = del->color;
    }

    delete del;

    if (originalColor == Node::BLACK)
    {
        deleteFixUp(moving);
    }
}

void RBTree::deleteFixUp(Node* node)
{
    while (node != root && node->color == Node::BLACK)
    {
        if (node == node->parent->left) //the node is left child
        {
            Node* sibling = node->parent->right;
            if (sibling->color == Node::RED) //the sibling is red
            {
                sibling->color = Node::BLACK;
                node->parent->color = Node::RED; 
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }
            if (sibling->left->color == Node::BLACK && sibling->right->color == Node::BLACK) //both child of sibling are black 
            {
                sibling->color = Node::RED;
                node = node->parent;
            }
            else
            {
                if (sibling->right->color == Node::BLACK) { //The sibling's right is black, the left is red
                    sibling->left->color = Node::BLACK;
                    sibling->color = Node::RED;
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color; //both sibling's child are red
                node->parent->color = Node::BLACK;
                sibling->right->color = Node::BLACK;
                rotateLeft(node->parent);
                node = root;
            }
        }
        else //mirror
        {
            Node* sibling = node->parent->left;
            if (sibling->color == Node::RED)
            {
                sibling->color = Node::BLACK;
                node->parent->color = Node::RED;
                rotateRight(node->parent);
                sibling = node->parent->left;
            }
            if (sibling->right->color == Node::BLACK && sibling->left->color == Node::BLACK)
            {
                sibling->color = Node::RED;
                node = node->parent;
            }
            else
            {
                if (sibling->left->color == Node::BLACK) {
                    sibling->right->color = Node::BLACK;
                    sibling->color = Node::RED;
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = Node::BLACK;
                sibling->left->color = Node::BLACK;
                rotateRight(node->parent);
                node = root;
            }
        }
    }

    node->color = Node::BLACK;
}

void RBTree::transplant(Node* current, Node* replacing)
{
    if (current->parent == &nil) //current is root
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
    replacing->parent = current->parent;
}

void RBTree::clear()
{
    clear(root);
    root = &nil;
}

void RBTree::clear(Node* node)
{
    if (node == &nil)
        return;
    
    clear(node->left);
    clear(node->right);
    delete node;
    root = &nil;
}