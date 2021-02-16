#pragma once

class Fibonacci
{
public:
    using key_t = int;
    using data_t = int;

    ~Fibonacci();
    void clear();

    bool empty() const;
    void insert(key_t key, data_t data = 0);
    key_t getMin() const;
    void unionAndDestroy(Fibonacci& f);
    key_t extractMin();
    void decreaseKey(key_t oldValue, key_t newValue);
    void erase(key_t key);
    bool isExist(key_t key);

    void output();
private:
    class Node
    {
    public:
        Node(key_t k, data_t d = 0);
        ~Node();

        Node* parent;
        Node* left;
        Node* right;
        struct Content
        {
            key_t key;
            data_t data;
            Node* child;
            size_t degree;
            bool mark;
        } content;

        bool isSingle() const;
        Node* find(key_t key);
    private:
        Node* find(key_t key, Node* startFrom);
    };

    Node* root = nullptr;
    size_t count = 0;

    void linkToRoot(Node* node);
    void unlinkToRoot(Node* node);
    void consolidate();
    void swap(Node* node1, Node* node2);
    void heapLink(Node* asChild, Node* asRoot);
    Node* find(key_t key);
    void cut(Node* node);
    void cascadingCut(Node* node);
};

