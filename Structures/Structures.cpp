// Structures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Fibonacci.h"

#include <iostream>
#include <assert.h>

int main()
{
    Fibonacci f;
    f.insert(5);
    f.insert(10);
    f.output();
    f.insert(15);
    f.output();
    
    std::cout << "union:" << std::endl;
    Fibonacci f2;
    f2.insert(8);
    f2.insert(1);
    f.unionAndDestroy(f2);
    f.output();

    std::cout << "get min=" << f.getMin() << std::endl;
    
    std::cout << std::endl;
    std::cout << "init: 56, 22, 84, 32, 85, 15, 16" << std::endl;
    f2.insert(56); f2.insert(22); f2.insert(84); f2.insert(32); f2.insert(85); f2.insert(15); f2.insert(16);
    f2.output();
    std::cout << std::endl;

    std::cout << "Extract min:" << std::endl;
    while (!f2.empty())
    {
        Fibonacci::key_t k = f2.extractMin();
        std::cout << k << ' ';
    }
    std::cout << std::endl;

    std::cout << "check clear" << std::endl;
    f2.insert(56); f2.insert(22); f2.insert(84); f2.insert(32); f2.insert(85); f2.insert(15); f2.insert(16);
    f2.output();
    f2.extractMin();
    f2.clear();
    bool res = f2.empty();
    std::cout << std::endl;

    std::cout << "decrease key 32" << std::endl;
    f2.insert(56); f2.insert(22); f2.insert(84); f2.insert(32); f2.insert(85); f2.insert(15); f2.insert(16);
    f2.extractMin();
    f2.decreaseKey(32, 5);
    f2.output();
    std::cout << std::endl;

    std::cout << "delete key 32" << std::endl;
    f2.clear();
    f2.insert(56); f2.insert(22); f2.insert(84); f2.insert(32); f2.insert(85); f2.insert(15); f2.insert(16);
    f2.extractMin();
    f2.erase(32);
    assert(!f2.isExist(32));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
