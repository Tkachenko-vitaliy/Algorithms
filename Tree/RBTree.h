#pragma once

class RBTree
{
public:
    ~RBTree();
    void insert(int key, int value);
    bool find(int key, int& value);
    void inorder();
    int min();
    int max();
    int morekey(int key);
    int lesskey(int key);
    int size();
    void erase(int key);
    void clear();
private:
    
    struct Node
    {
        Node(Node* parent=nullptr, int key = 0, int value = 0)
        {
            left = nullptr; right = nullptr; this->parent = parent; this->key = key; this->value = value; color = BLACK;
        }
        
        enum Color { BLACK = 0, RED = 1 };

        Node* left;
        Node* right;
        Node* parent;
        int key;
        int value;
        Color color;
    };

    Node nil;
    Node* root = &nil;

    void InsertFixUp(Node* node);
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void transplant(Node* current, Node* replacing);
    void deleteFixUp(Node* node);
    
    Node* find(int key);
    void inorder(Node* node);
    Node* max(Node* node);
    Node* min(Node* node);
    void clear(Node* node);
};

