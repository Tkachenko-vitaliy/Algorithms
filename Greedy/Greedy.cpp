// Greedy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Huffman.h"

#include <sstream>
#include <string.h>

using namespace std;

int main()
{
    string teststring;
    teststring.append(45, 'a');
    teststring.append(13, 'b');
    teststring.append(12, 'c');
    teststring.append(16, 'd');
    teststring.append(9, 'e');
    teststring.append(5, 'f');

    istringstream stream;
    stream.str(teststring);

    cout << "source: " << endl;
    cout << teststring << endl;

    Huffman h;
    h.assign(stream);
    cout << "encoded: " << endl;
    h.getEncoded(cout);
    cout << endl;
    cout << "decoded: " << endl;
    h.getDecoded(cout);
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
