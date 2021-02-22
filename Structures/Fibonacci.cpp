#include "Fibonacci.h"

#include <vector>
#include <cmath>
#include <assert.h>

Fibonacci::Node::Node(key_t k, data_t d)
{
    parent = nullptr; 
    left = this; right = this;
    content.child = nullptr;
    content.degree = 0;
    content.key = k;
    content.data = d;
    content.mark = false;
};

Fibonacci::Node::~Node()
{
    if (content.child)
    {
        if (content.child->left == content.child->right)
        {
            content.child->left = nullptr; //break the ring
        }
        else
        {
            content.child->right->left = nullptr; //break the chain
        }

    }

    delete content.child;
    delete left;
}

Fibonacci::Node* Fibonacci::Node::find(key_t key)
{
    if (content.key == key)
    {
        return this;
    }

    Node* node = left->find(key, this);

    if (node)
    {
        return node;
    }

    if (content.child)
    {
        return content.child->find(key);
    }

    return nullptr;
}

Fibonacci::Node* Fibonacci::Node::find(key_t key, Node* startFrom)
{
    if (startFrom == this)
    {
        return nullptr;
    }

    if (content.key == key)
    {
        return this;
    }

    Node* node = left->find(key, startFrom);

    if (node)
    {
        return node;
    }

    if (content.child)
    {
        return content.child->find(key);
    }

    return nullptr;
}

bool Fibonacci::Node::isSingle() const
{
    return left == right;
}

Fibonacci::~Fibonacci()
{
    clear();
}

void Fibonacci::clear()
{
    if (root)
    {
        if (root->isSingle())
        {
            root->left = nullptr; //break the ring
        }
        else
        {
            root->right->left = nullptr; //break the chain
        }

        delete root;
    }

    root = nullptr;
}

void Fibonacci::insert(key_t key, data_t data)
{
    if (root == nullptr)
    {
        root = new Node(key, data);
        root->left = root;
        root->right = root;
    }
    else
    {
        Node* node = new Node(key, data);
        linkToRoot(node);
        
        if (key < root->content.key)
        {
            root = node;
        }
    }

    count++;
}

void Fibonacci::linkToRoot(Node* node)
{
    Node* left = root->left;

    node->right = root;
    node->left = left;
    left->right = node;
    root->left = node;
    if (root->right == root)
    {
        root->right = node;
    }

    node->parent = nullptr;
}

void Fibonacci::unlinkToRoot(Node* node)
{
    if (node->left == node && node->right == node) //the single root
    {
        root = nullptr;
    }
    else
    {
        Node* left = node->left;
        Node* right = node->right;
        left->right = right;
        right->left = left;
    }
}

bool Fibonacci::empty() const
{
    return root == nullptr;
}

Fibonacci::key_t Fibonacci::getMin() const
{
    assert(root);
    return root->content.key;
}

void Fibonacci::unionAndDestroy(Fibonacci& f)
{
    //add to the right edge
    f.root->left->right = nullptr; //break the chain
    Node* node = f.root->right;
    linkToRoot(f.root);
    while (node)
    {
        Node* right = node->right;
        linkToRoot(node);
        node = right;
    }

    count += f.count;
    if (f.root->content.key < root->content.key)
    {
        root = f.root;
    }

    f.root = nullptr;
}

Fibonacci::key_t Fibonacci::extractMin()
{
    assert(root); 
    Node* node = root->content.child;

    if (node)
    {
        node->left->right = nullptr; //break the chain
    }

    while (node)
    {
        node->parent = nullptr;
        Node* right = node->right;
        linkToRoot(node);
        node = right;
    }

    Node* minKeyNode = root;
    unlinkToRoot(root);

    if (root)
    {
        root = root->right;
        consolidate();
    }

    count--;

    key_t k = minKeyNode->content.key;
    minKeyNode->left = nullptr;
    minKeyNode->right = nullptr;
    minKeyNode->content.child = nullptr;
    delete minKeyNode;
    return k;
}

void Fibonacci::consolidate()
{
    size_t maxDegree = (size_t)(ceil(log2(count)) + 1);
    std::vector<Node*> arRootDegree(maxDegree, nullptr);
    Node* current = root;

    while (arRootDegree[current->content.degree] != current)
    {
        size_t degree = current->content.degree;

        while (arRootDegree[degree] != nullptr)
        {
            Node* conflict = arRootDegree[degree];
            if (current->content.key > conflict->content.key)
            {
                swap(current, conflict);
            }
            heapLink(conflict, current);
            arRootDegree[degree] = nullptr;
            degree++;
        }

        arRootDegree[degree] = current;
        current = current->right;

    } 

    root = nullptr;

    for (Node* node : arRootDegree)
    {
        if (node)
        {
            if (root ==  nullptr)
            {
                root = node;
            }
            else
            {
                if (node->content.key < root->content.key)
                {
                    root = node;
                }
            }
        }
    }
}

void Fibonacci::swap(Node* node1, Node* node2)
{
    
    Node::Content temp = node2->content;
    node2->content = node1->content;
    node1->content = temp; 
}

void Fibonacci::heapLink(Node* asChild, Node* asRoot)
{
    unlinkToRoot(asChild);
    asChild->parent = asRoot;
    asChild->left = nullptr;
    asChild->right = nullptr;
    if (asRoot->content.child == nullptr)
    {
        asRoot->content.child = asChild;
        asChild->left = asChild;
        asChild->right = asChild;
    }
    else
    {
        Node* chainNode = asRoot->content.child;
        Node* left = chainNode->left;
        chainNode->left = asChild;
        asChild->right = chainNode;
        asChild->left = left;
        if (chainNode->right == chainNode)
        {
            chainNode->right = asChild;
        }
    }
        
    asRoot->content.degree++;
    asChild->content.mark = false;
}

void Fibonacci::decreaseKey(key_t oldValue, key_t newValue)
{
    //We find the item with key. It is slow; it might be better to use a pointer to item as input parameter instead of key value. 
    //That is, to use the pointer to the Node* as iterator.
    //If so, we will have to return appropriate pointer from insert method
    Node* node = find(oldValue);
    assert(node); //key is not presented
    assert(newValue <= oldValue);

    node->content.key = newValue;

    Node* parent = node->parent;

    if (parent != nullptr && newValue < parent->content.key)
    {
        cut(node);
        cascadingCut(parent);
    }

    if (node->content.key < root->content.key)
    {
        root = node;
    }
}

void Fibonacci::cut(Node* node)
{
    Node* parent = node->parent;
    if (node->isSingle())
    {
        parent->content.child = nullptr;
    }
    else
    {
        Node* left = node->left;
        Node* right = node->right;
        left->right = right;
        right->left = left;
        parent->content.child = left;
        left->parent = parent;
    }

    parent->content.degree--;

    node->content.mark = false;
    linkToRoot(node);
}

void Fibonacci::cascadingCut(Node* node)
{
    Node* parent = node->parent;
    if (parent == nullptr)
    {
        return;
    }

    if (node->content.mark == false)
    {
        node->content.mark = true;
    }
    else
    {
        cut(node);
        cascadingCut(parent);
    }
}

Fibonacci::Node* Fibonacci::find(key_t key)
{
    if (!root)
    {
        return nullptr;
    }
    else
    {
        return root->find(key);
    }
}

void Fibonacci::erase(key_t key)
{
    //Slow operation - see notes for decreaseKey method
    Node* node = find(key);

    if (node == nullptr)
    {
        return;
    }

    Node* parent = node->parent;

    if (parent != nullptr)
    {
        cut(node);
        cascadingCut(parent);
    }

    root = node;
    extractMin();
}

bool Fibonacci::isExist(key_t key)
{
    return find(key) != nullptr;
}

#include<iostream>

void Fibonacci::output()
{
    if (root == nullptr)
    {
        std::cout << "empty" << std::endl;
        return;
    }
    Node* node = root;
    std::cout << node->content.key << ' ';
    node = node->right;
    while (node != root)
    {
        std::cout << node->content.key << ' ';
        node = node->right;
    }

    std::cout << std::endl;

}
