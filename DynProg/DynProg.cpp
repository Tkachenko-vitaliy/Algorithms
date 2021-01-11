// DynProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <algorithm>

class RodCutter
{
public:
    void setPrices(std::initializer_list<unsigned int> prices) {
        priceList = prices;
    };
    unsigned int descendingMax(unsigned int length);  //Only recursion
    unsigned int descendingMax2(unsigned int length); //with memoization
    unsigned int ascendingMax(unsigned int length);   
    unsigned int ascendingMax(unsigned int length, std::vector<unsigned int>& parts); 
private:
    std::vector<unsigned int> priceList;
    unsigned int descendingMax2(unsigned int length, std::vector<int>& memoizedValue);
};

unsigned int RodCutter::descendingMax(unsigned int length)
{
    if (length == 0)
        return 0;
    unsigned int optimum = 0;
    for (size_t i = 1; i <= length; i++)
    {
        optimum = std::max(optimum, priceList[i-1] + descendingMax(length - i));
    }

    return optimum;
}

unsigned int RodCutter::descendingMax2(unsigned int length)
{
    std::vector<int> memoizedValue;
    memoizedValue.assign(length, 0);
    return descendingMax2(length, memoizedValue);
}

unsigned int RodCutter::descendingMax2(unsigned int length, std::vector<int>& memoizedValue)
{
    if (length == 0)
        return 0;
   if (memoizedValue[length-1] > 0)
        return memoizedValue[length-1];
   unsigned int optimum = 0;
   for (size_t i = 1; i <= length; i++)
   {
       unsigned int nextOpt = priceList[i - 1] + descendingMax2(length - i, memoizedValue);
       optimum = std::max(optimum, nextOpt);
   }
   memoizedValue[length - 1] = optimum;
   return optimum;
}

unsigned int RodCutter::ascendingMax(unsigned int length)
{
    std::vector<int> memoizedValue;
    memoizedValue.assign(length+1, 0);

    for (unsigned int j = 1; j <= length; j++)
    {
        unsigned int optimum = 0;
        for (unsigned int i = 1; i <= j; i++)
        {
            unsigned int nextOpt = priceList[i - 1] + memoizedValue[j - i];
            optimum = std::max(optimum, nextOpt);
        }
        memoizedValue[j] = optimum;
    }

    return memoizedValue[length];
}

unsigned int RodCutter::ascendingMax(unsigned int length, std::vector<unsigned int>& parts)
{
    std::vector<unsigned int> memoizedValue, firstPartLength;
    memoizedValue.assign(length + 1, 0);
    firstPartLength.assign(length + 1, 0);

    for (unsigned int j = 1; j <= length; j++)
    {
        unsigned int optimum = 0;
        for (unsigned int i = 1; i <= j; i++)
        {
            unsigned int nextOpt = priceList[i - 1] + memoizedValue[j - i];
            if (nextOpt > optimum)
            {
                firstPartLength[j] = i;
            }
            optimum = std::max(optimum, nextOpt);
        }
        memoizedValue[j] = optimum;
    }

    unsigned int partLengthIndex = length;
    while (firstPartLength[partLengthIndex] != 0)
    {
        parts.push_back(firstPartLength[partLengthIndex]);
        partLengthIndex = partLengthIndex - firstPartLength[partLengthIndex];
    }

    return memoizedValue[length];
}


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
