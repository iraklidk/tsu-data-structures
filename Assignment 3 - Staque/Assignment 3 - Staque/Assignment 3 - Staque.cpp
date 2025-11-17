#include <iostream>
#include <vector>
#include "staque.h"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(static_cast<unsigned int>(time(0))); // seed random generator

    staque s;

    // Add 50 random numbers between 1 and 100
    for (int i = 0; i < 50; ++i) {
        int value = rand() % 100 + 1; // 1..100
        s.add(value);
    }

	// Copy constructor test
    staque oth = s;

    // Print the staque
    cout << "Current Staque: " << oth << endl;

    // Test peek
    cout << "Peek element: " << oth.peek() << endl;

    // Get elements by parity
    vector<int> odds = oth.getElements(true);
    vector<int> evens = oth.getElements(false);

    // Print size test
	cout << "Size of staque: " << oth.size() << endl;

	// Print odd and even elements size test
	cout << "Odd count: " << odds.size() << ", Even count: " << evens.size() << endl;

    // Search test
	oth.search(32) ? cout << "32 found in staque." << endl : cout << "32 not found in staque." << endl;
    oth.search(12) ? cout << "12 found in staque." << endl : cout << "12 not found in staque." << endl;
    oth.search(9) ? cout << "9 found in staque." << endl : cout << "9 not found in staque." << endl;
    oth.search(35) ? cout << "35 found in staque." << endl : cout << "35 not found in staque." << endl;

    // Print odd and even elements
    cout << "Odd elements: ";
    for (int v : odds) cout << v << " ";
    cout << endl;

    cout << "Even elements: ";
    for (int v : evens) cout << v << " ";
    cout << endl;

	oth.deleteValues(1, 10); // Delete 10 odd elements
	cout << "After deleting 10 odd elements, staque: " << oth << endl;
	oth.deleteValues(0, 10); // Delete 10 even elements
    cout << "After deleting 10 even elements, staque: " << oth << endl;

    staque some;
    cout << "Current some staque " << some << endl;

    // Add 50 random numbers between 1 and 100
    for (int i = 0; i < 100; ++i) {
        int value = rand() % 100 + 1; // 1..100
        some.add(value);
    }

	some.deleteValues(1, 20); // Delete 20 odd elements
	cout << "Some staque after deleting 20 odd elements: " << some << endl;

	some.deleteValues(30); // Delete 30 elements by default
    cout << "Some staque after deleting 30 elements by default: " << some << endl;

	return 0;
}