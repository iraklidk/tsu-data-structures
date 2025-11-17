#pragma once
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

class staque
{
public:

	// Returns the last added element, returns -1 if staque is empty
	int peek();

	// Returns true if value is in staque, otherwise false
	bool search(int value);

	// if deleteEven is 1 deletes 'count' odd elements, if deleteEven is 0 deletes 'count' even elements, if deleteEven is -1 delete 'count' element by default deleteEven is -1 and count is 1
	void deleteValues(int deleteEven = -1, int count = 1);

	// Adds an element in the staque
	void add(int value);

	// if parity is flase returns even elements, otherwise returns odd elements. by default parity is false. if staque is empty return empty vector
	vector<int> getElements(bool parity = 0);

	// Default constructor
	staque();

	// Copy constructor
	staque(const staque& other);

	// Destructor
	~staque();

	// returns total size of staque
	int size(); 

	friend ostream& operator<<(ostream& os, const staque& s);

private:
	// Stores the last added element's parity
	stack<bool> peekParity;

	// Stores counts of even and odd elements
	int evens, odds;

	// Declare node for double linked list
	struct Node
	{
		int value;
		Node* next;
		Node* prev;

		Node(int value) : value(value), next(nullptr), prev(nullptr) {}
	};

	Node* head; // pointer to first node
	Node* tail; // pointer to last node

	bool checkElementsByParity(int value); // helper function return true if at least 1 element exist
};