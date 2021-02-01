#pragma once

#include <vector>

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
