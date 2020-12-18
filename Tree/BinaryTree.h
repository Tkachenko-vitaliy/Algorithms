#pragma once

class BinaryTree
{
public:
    ~BinaryTree();
    void insert(int key, int value);
    bool find(int key, int& value);
    void inorder();
    void preorder();
    void postorder();
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
        Node(Node* parent, int key, int value)
        {
            left = nullptr; right = nullptr; this->parent = parent; this->key = key; this->value = value;
        }
        ~Node() { delete left; delete right; }

        void destroy() { left = nullptr; right = nullptr; delete this; }

        Node* left;
        Node* right;
        Node* parent;
        int key;
        int value;
    };


    Node* root = nullptr;
    Node* find(int key);
    void inorder(Node* node);
    void preorder(Node* node);
    void postorder(Node* node);
    Node* max(Node* node);
    Node* min(Node* node);
    int size(Node* node);
    void transplant(Node* current, Node* replacing);
};

