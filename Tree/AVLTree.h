#pragma once

class AVLTree
{
public:
    void insert(int key, int value);
    size_t getHeightLeft();
    size_t getHeightRight();

    void output(bool showBalance = false);
private:

    using balance_t = char;

    struct Node
    {
        Node(int k = 0, int v = 0)
        {
            left = nullptr; right = nullptr; key = k; value = v; balance = 0;
        }

        Node* left;
        Node* right;
        int key;
        int value;
        balance_t balance;
    };

    Node* root = nullptr;

    Node* insert(Node* node, int key, int value, bool& heightChanged);

    Node* checkBalance(Node* node, balance_t offset, bool& heightChanged);
    Node* rebalance(Node* node, balance_t newBalance,  bool& heightChanged);

    Node* rotateLeftSmall(Node* node);
    Node* rotateRightSmall(Node* node);
    Node* rotateLeftBig(Node* node);
    Node* rotateRightBig(Node* node);

    void output(Node* node, bool showBalance, unsigned int level);
};
