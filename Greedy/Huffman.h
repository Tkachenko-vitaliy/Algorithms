#pragma once

#include <vector>
#include <iostream>
#include <cassert>
#include <map>

struct Node
{
    Node(unsigned int freq = 0) : frequency(freq) {}
    ~Node() { delete left; delete right; }

    unsigned int frequency = 0;

    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    virtual char getChar() const { assert(false); return 0;  } //Valid only for leaf
    bool isLeaf() const { return left == nullptr && right == nullptr; }
};

struct Leaf : Node
{
    Leaf(unsigned int freq = 0, char sym = 0) : Node(freq), symbol(sym) {}
    char symbol;

    char getChar() const override { return symbol; }
};

class Huffman
{
public:
    void assign(std::istream& stream);
    void getEncoded(std::ostream& stream);
    void getDecoded(std::ostream& stream);
private:
    using CodeString = std::vector<bool>;

    CodeString encodedData;
    std::unique_ptr<Node> codeTree;
    std::map<char, unsigned int> frequencyMap;
    std::map<char, CodeString> dictionary;
    unsigned long curPosEncodedData;

    void createFrequencyMap(std::istream& stream);
    void createCodeTree();
    void createDictionary();
    void encode(std::istream& stream);
    void iterateTree(Node* node);
    bool isChildLeft(Node* nodeChild);
    bool isChildRight(Node* nodeChild);
    void pushBits(CodeString& code);
    void resetPosData();
    bool getDataBit();
    bool eof();
};

