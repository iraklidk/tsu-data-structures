#include <iostream>
#include<string>
using namespace std;

void encode(string* input, int* shift) {
	cout << "Encoded passphrase: ";
	for (char* it = &(*input)[0]; *it != '\0'; ++it) { // it holds iterator
		if (*it >= 'a' && *it <= 'z') {
			cout << char(((*it - 'a' + *shift) % 26) + 'a'); // if lowercase
		}
		else if (*it >= 'A' && *it <= 'Z') {
			cout << char(((*it - 'A' + *shift) % 26) + 'A'); // if uppercase
		}
		else {
			cout << *it; // non-letter stays the same
		}
	}
	cout << "\n\n";
}

void decode(string* input, int* shift) {
	*shift %= 26;
	cout << "Decoded passphrase: ";
	for (char* it = &(*input)[0]; *it != '\0'; ++it) { // it holds iterator
		if (*it >= 'a' && *it <= 'z') {
			cout << char(((*it - 'a' - *shift + 26) % 26) + 'a'); // if lowercase
		}
		else if (*it >= 'A' && *it <= 'Z') {
			cout << char(((*it - 'A' - *shift + 26) % 26) + 'A'); // if uppercase, + 26 to handle if the possible ascii code is negative
		}
		else {
			cout << *it; // non-letter stays the same
		}
	}
	cout << "\n\n";
}

int main()
{
	cout << "Loading Enigma...\n" << endl;
	while (true) {
		cout << "Enter a passphrase (q to quit): ";
		string* input = new string;
		getline(cin, *input);
		if ((*input).size() == 1 && (*input)[0] == 'q') break;

		cout << "Select an operation:\n 1.Encode\n 2.Decode\nEnter your choice(1 / 2): ";
		int* op = new int;
		cin >> *op;

		while (*op != 1 && *op != 2) {
			cout << "Please input 1 or 2: ";
			cin >> *op;
		}

		cout << "Enter a shift: ";
		int* shift = new int;
		cin >> *shift;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

		if (*op == 1) encode(input, shift);
		else decode(input, shift);

		delete op;
		delete shift;
		delete input; // avoid memory leaks
	}
}