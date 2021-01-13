// Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

class Pyramid
{
public:
    void assign(std::initializer_list<int> assignedData) {data = assignedData; }
    void buildPyramid();
    void sort();
    void print();
private:
    vector<int> data;
    int parent(int index) { return index / 2; }
    int left(int index)   { return index * 2; }
    int right(int index) { return index * 2 + 1; }
    int get(int index) { return data[index - 1]; }
    void set(int index, int value) { data[index - 1] = value; }
    void swap(int first, int second);
    void maxHeapify(int index, int heapSize);
    void buildMaxHeap();
};

void Pyramid::print()
{
    for (auto item : data)
    {
        cout << item << ' ';
    }
}

void Pyramid::swap(int first, int second)
{
    int temp = get(second);
    set(second, get(first));
    set(first,temp);
}

void Pyramid::maxHeapify(int index, int heapSize)
{
    int leftChildIndex = left(index);
    int rightChildIndex = right(index);
    int largestIndex = index; 
    //Find max index from paren, left-child, right-child. Index is a parent node
    if (leftChildIndex <= heapSize && get(leftChildIndex) > get(index))
    {
        largestIndex = leftChildIndex;
    }
    if (rightChildIndex <= heapSize && get(rightChildIndex) > get(largestIndex))
    {
        largestIndex = rightChildIndex;
    }

    if (largestIndex != index)
    {
        swap(index, largestIndex);
        maxHeapify(largestIndex,heapSize);
    }
}

void Pyramid::buildMaxHeap()
{
    int length = data.size() / 2;
    for (int index = length; index >=1; index--)
    {
        maxHeapify(index, data.size());
    }
}

void Pyramid::buildPyramid()
{
    buildMaxHeap();
}

void Pyramid::sort()
{
    buildMaxHeap();
    int heapSize = data.size();
    for (int i = data.size(); i >= 2; i--)
    {
        swap(1, i);
        heapSize--;
        maxHeapify(1, heapSize);
    }
}

int main()
{
    Pyramid pyramid;
    pyramid.assign({4,1,3,2,16,9,10,14,8,7});
    cout << "Source:" << endl;
    pyramid.print();
    cout << endl;
    pyramid.buildPyramid();
    cout << "Build Pyramid: " << endl;
    pyramid.print();
    cout << endl;
    pyramid.assign({ 4,1,3,2,16,9,10,14,8,7 });
    pyramid.sort();
    cout << "sorted:" << endl;
    pyramid.print();
    cout << endl;
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
