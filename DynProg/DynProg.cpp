// DynProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "RodCutter.h"

#include <iostream>

int main()
{
    RodCutter cutter;
    cutter.setPrices({ 1,5,8,9,10,17,17,20,24,30 });
    
    std::cout << "descendingMax:" << std::endl;
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << i+1 << " << " << cutter.descendingMax(i + 1) << std::endl;
    }

    std::cout << std::endl;

    std::cout << "descendingMax2: memoization" << std::endl;
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << i + 1 << " << " << cutter.descendingMax2(i + 1) << std::endl;
    }

    std::cout << std::endl;

    std::cout << "ascendingMax:" << std::endl;
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << i + 1 << " << " << cutter.ascendingMax(i + 1) << std::endl;
    }

    std::cout << std::endl;
    std::cout << "ascendingMax solution:" << std::endl;
    for (size_t i = 0; i < 10; i++)
    {
        std::vector<unsigned int> parts;
        unsigned int q = cutter.ascendingMax(i + 1, parts);
        std::cout << i + 1 << " << " << q << " [";
        for (size_t i = 0; i < parts.size(); i++)
        {
            std::cout << parts[i] << ',';
        }
        std::cout << "]" << std::endl;
    }
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
