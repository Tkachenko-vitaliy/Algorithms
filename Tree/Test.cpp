#include "Test.h"
#include "BinaryTree.h"
#include "RBTree.h"

#include <iostream>
#include <assert.h>

using namespace std;

void CheckErase(BinaryTree& tree, int key)
{
    int value;
    tree.clear();
    tree.insert(1, 100); tree.insert(5, 500); tree.insert(7, 700); tree.insert(3, 300);  tree.insert(9, 900);
    tree.insert(6, 600); tree.insert(2, 200); tree.insert(8, 800); tree.insert(4, 400);
    cout << "erase " << key << ": ";
    tree.erase(key);
    tree.inorder(); cout << endl;
    assert(tree.find(key, value) == false);
}

void CheckErase(RBTree& tree, int key)
{
    int value;
    tree.clear();
    tree.insert(1, 100); tree.insert(5, 500); tree.insert(7, 700); tree.insert(3, 300);  tree.insert(9, 900); tree.insert(6, 600); tree.insert(2, 200); tree.insert(8, 800); tree.insert(4, 400);
    tree.insert(12, 120); tree.insert(19, 190); tree.insert(20, 200); tree.insert(15, 150); tree.insert(14, 140); tree.insert(13, 130); tree.insert(16, 160); tree.insert(17, 170); tree.insert(18, 180);
    cout << "erase " << key << ": ";
    tree.erase(key);
    tree.inorder(); cout << endl;
    assert(tree.find(key, value) == false);
}


void TestBinaryTree()
{
    cout << "TestBinaryTree..." << endl;
    BinaryTree tree;
    tree.insert(1, 100); tree.insert(7, 700); tree.insert(5, 500); tree.insert(3, 300);  tree.insert(9, 900);

    int value; bool fres;
    fres = tree.find(3, value);
    assert(fres && value == 300);
    fres = tree.find(0, value);
    assert(!fres);
    fres = tree.find(7, value);
    assert(fres && value == 700);
    fres = tree.find(1, value);
    assert(fres && value == 100);
    fres = tree.find(6, value);
    assert(!fres);
    fres = tree.find(10, value);
    assert(!fres);

    cout << "inorder:" << endl;
    tree.inorder(); cout << endl;
    cout << "preorder:" << endl;
    tree.preorder(); cout << endl;
    cout << "postorder:" << endl;
    tree.postorder(); cout << endl;

    assert(tree.min() == 1);
    assert(tree.max() == 9);

    assert(tree.morekey(10) == -1);
    assert(tree.morekey(2) == 3);
    assert(tree.morekey(8) == 9);

    assert(tree.lesskey(10) == 9);
    assert(tree.lesskey(0) == -1);
    assert(tree.lesskey(7) == 7);
    assert(tree.lesskey(6) == 5);

    assert(tree.size() == 5);

    CheckErase(tree, 1);
    CheckErase(tree, 7);
    CheckErase(tree, 5);
    CheckErase(tree, 3);
    CheckErase(tree, 9);

    cout << endl;
}

void TestRBTree()
{
    cout << "TestRBTree..." << endl;
    RBTree tree;

    tree.insert(1, 100); tree.insert(7, 700); tree.insert(5, 500); tree.insert(3, 300);  tree.insert(9, 900);

    int value; bool fres;
    fres = tree.find(3, value);
    assert(fres && value == 300);
    fres = tree.find(0, value);
    assert(!fres);
    fres = tree.find(7, value);
    assert(fres && value == 700);
    fres = tree.find(1, value);
    assert(fres && value == 100);
    fres = tree.find(6, value);
    assert(!fres);
    fres = tree.find(10, value);
    assert(!fres);

    cout << "inorder:" << endl;
    tree.inorder();
    cout << endl;

    tree.clear();
    cout << "erase pattern: "; 
    tree.insert(1, 100); tree.insert(5, 500); tree.insert(7, 700); tree.insert(3, 300);  tree.insert(9, 900);
    tree.insert(6, 600); tree.insert(2, 200); tree.insert(8, 800); tree.insert(4, 400);
    tree.inorder();
    cout << endl;

    CheckErase(tree, 1);
    CheckErase(tree, 7);
    CheckErase(tree, 5);
    CheckErase(tree, 3);
    CheckErase(tree, 9);

    cout << endl;
}