#pragma once

#include <list>

/*
It is a priority queue. 
Standard STL priority_queue does not suppot some necessary operations, such as "find item" and "change priority"
As container, I used a list.  It is not the best option, it would be much better to use binary pyramid. However, I was lazy to implement it.
Here non-increasing queue is implemented: the head list item is the most, the tail list item is the least.
*/
template <typename T, typename Compare = std::less<T> >
class PriorityQueue
{
public:
    using iterator = typename std::list<T>::iterator;
    using reference = typename std::list<T>::reference;
    using const_reference = typename std::list<T>::const_reference;

    iterator begin() { return queue.begin(); }
    iterator end() { return queue.end(); } 

    void push(const T& item);
    T pop();
    reference back() { return queue.back(); };
    reference front() { return queue.front(); }
    bool empty() const { return queue.empty(); }
    void clear() { queue.clear(); }

    
    void decrease_priority(iterator item);

private:
    using container = typename std::list<T>;
    container queue;
    Compare comp;
};

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::push(const T& item)
{
    typename container::iterator it = queue.begin();
    while (it != queue.end() && comp(item, (*it)) )
    {
        it++;
    }

    queue.insert(it, item);
}

template <typename T, typename Compare>
T PriorityQueue<T, Compare>::pop()
{
    T item = queue.back();
    queue.pop_back();
    return item;
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::decrease_priority(iterator item)
{
    typename container::iterator nextItem = item;
    nextItem++;
    while (nextItem != queue.end() && comp(*item , *nextItem))
    {
        nextItem++;
    }

    if (nextItem != item)
    {
        queue.insert(nextItem, *item);
        queue.erase(item);
    }
}



