#include "RodCutter.h"
#include <algorithm>

unsigned int RodCutter::descendingMax(unsigned int length)
{
    if (length == 0)
        return 0;
    unsigned int optimum = 0;
    for (size_t i = 1; i <= length; i++)
    {
        optimum = std::max(optimum, priceList[i - 1] + descendingMax(length - i));
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
    if (memoizedValue[length - 1] > 0)
        return memoizedValue[length - 1];
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
    memoizedValue.assign(length + 1, 0);

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
