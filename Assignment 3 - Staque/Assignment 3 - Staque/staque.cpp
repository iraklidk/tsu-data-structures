#include "staque.h"

int staque::peek()
{
    if (peekParity.empty()) {
        cerr << "staque is empty" << endl;
        return -1;
    }
    return peekParity.top() ? head->value : tail->value;
}

bool staque::search(int value)
{
    if(!checkElementsByParity(value)) return 0;
    int c = 0;
    if (value & 1) {
        Node* curr = head;
        while (curr)
        {
            if (c == odds) return 0;
            if (curr->value == value) return 1;
            c++;
            curr = curr->next;
        }
    }
    else {
        Node* curr = tail;
        while (curr)
        {
            if (c == evens) return 0;
            if (curr->value == value) return 1;
            c++;
            curr = curr->prev;
        }
    }

    return 0;
}

void staque::deleteValues(int deleteEven, int count)
{
    if (deleteEven == 1 && odds < count) {
        cerr << "Not enough odd elements to delete" << endl;
		return;
    }
    if (deleteEven == 0 && evens < count) {
        cerr << "Not enough even elements to delete" << endl;
        return;
    }
	if (count <= 0) {
        cerr << "Invalid parameter to func" << endl;
        return;
    }

    // For update stack
    vector<bool> tempStack;

    if (deleteEven == 1) { // Delete odds from head
        for (int i = 0; i < count; ++i) {
            Node* temp = head;
            if (!temp) break;

            head = head->next;       // Move head to next
            if (head) head->prev = nullptr;
            delete temp;

            odds--;
        }
        
        while (!peekParity.empty()) {
            bool isOdd = peekParity.top();
            peekParity.pop();
            if (isOdd) {
                if (tempStack.size() < count) {
                    count--;
                    continue; // Skip this odd parity
                }
            }
            tempStack.push_back(isOdd);
        }
        // Rebuild the peekParity stack
        for (int i = tempStack.size() - 1; i >= 0; --i) {
            peekParity.push(tempStack[i]);
		}
    }

    else if (deleteEven == 0) { // Delete evens from tail
        for (int i = 0; i < count; ++i) {
            Node* temp = tail;
            if (!temp) break;

            tail = tail->prev;       // Move tail to previous
            if (tail) tail->next = nullptr;
            delete temp;

            evens--;
        }
        while (!peekParity.empty()) {
            bool isOdd = peekParity.top();
            peekParity.pop();
            if (!isOdd) {
                if (tempStack.size() < count) {
                    count--;
                    continue; // skip this even parity
                }
            }
            tempStack.push_back(isOdd);
        }
        // Rebuild the peekParity stack
        for (int i = tempStack.size() - 1; i >= 0; --i) {
            peekParity.push(tempStack[i]);
        }


    }
    else if (deleteEven == -1) { // delete LIFO based on peekParity
        for (int i = 0; i < count; ++i) {
            bool isOdd = peekParity.top();
            peekParity.pop();

            if (isOdd && head) {
                Node* temp = head;
                head = head->next;
                if (head) head->prev = nullptr;
                delete temp;
                odds--;
            }
            else if (!isOdd && tail) {
                Node* temp = tail;
                tail = tail->prev;
                if (tail) tail->next = nullptr;
                delete temp;
                evens--;
            }
        }
    }
}

void staque::add(int value) {
    Node* newNode = new Node(value);

    // If staque is empty
    if (odds == 0 && evens == 0) {
        head = tail = newNode;   // First element is both head and tail
        if (value & 1) odds++;   // Update counts
        else evens++;
        peekParity.push(value & 1);
        return;
    }

    if (value & 1) { // Odd: add to left
        newNode->next = head;  // Point to previous last odd
        if (head) head->prev = newNode;
        head = newNode;
        odds++;
    }
    else { // even: add to right
        newNode->prev = tail;  // point to previous last even
        if (tail) tail->next = newNode;
        tail = newNode;
        evens++;
    }

    peekParity.push(value & 1); // store parity
}


vector<int> staque::getElements(bool parity)
{
    if (!checkElementsByParity(parity)) {
        cerr << "staque is empty" << endl;
        return {};
    }
    
    int c = 0;
    vector<int> res;

	// If parity is true, return odd elements
    if (parity) {
        Node* curr = head;
        while (c != odds) {
            res.push_back(curr->value);
            c++;
            curr = curr->next;
        }
    }

	// If parity is false, return even elements
    else {
        Node* curr = tail;
        while (c != evens) {
            res.push_back(curr->value);
            c++;
            curr = curr->prev;
        }
    }

    return res;
}

staque::staque() : head(nullptr), tail(nullptr), odds(0), evens(0), peekParity() { }

staque::staque(const staque& other)
{
    head = tail = nullptr;
    evens = other.evens;
    odds = other.odds;
    peekParity = other.peekParity;

    // If there are no nodes at all, just return
    if (!other.head && !other.tail) return;

    // Start from the first node in the original list
    Node* currOther = other.head;
    Node* prevNew = nullptr;

    while(currOther) {
        // Create a new node with the same value
        Node* newNode = new Node(currOther->value);
        // Link the new node to the previous node in the new list
        if (prevNew)
        {
            prevNew->next = newNode;
            newNode->prev = prevNew;
        }
        else head = newNode;

        // Move prevNew to the newly created node
        prevNew = newNode;

        // If this is the last node in the original list, set tail
        if (!currOther->next) tail = newNode;

        // Move to the next node in the original list
        currOther = currOther->next;
	}
}

staque::~staque()
{
    Node* curr = head;
    while (curr)
    {
        Node* temp = curr;
        curr = curr->next;
        delete temp; // Free allocated memory
    }
}

bool staque::checkElementsByParity(int value)
{
    return !((value & 1 && !odds) || (!(value & 1) && !evens));
}

int staque::size()
{
    return odds + evens;
}

ostream& operator<<(ostream& os, const staque& s)
{
    auto curr = s.head;
    while (curr)
    {
        os << curr->value << " ";
        curr = curr->next;
    }
    return os;
}