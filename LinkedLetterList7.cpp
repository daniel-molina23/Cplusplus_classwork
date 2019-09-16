/*
Name: Daniel Molina
Class: CS52
Lab #: 7
Compiler Used: Visual Studio
Operating System Used: Windows 10
Date and Time of Last successful Compilation: 4/21/2019 11:53am
Date and Time of when program verified all test results: 4/22/2019 2pm
*/


#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;
class LetterFrequencyList {
private:
	struct LetterNode {

		char letter; //letter within the phrase or paragraphs inputted
		LetterNode * Next; //pointer 'next' to the next letter node
		size_t frequency; //number of times the letter appears

		LetterNode(char ch, size_t frq, LetterNode* ptr) {
			letter = ch;
			frequency = frq;
			Next = ptr;
		}
		const string toString() {
			return "Letter " + string(1, letter) + " occurred: " + to_string(frequency) + " times.";
		}

	};
	LetterNode* HeadPtr;
	LetterNode* contains(char ltr);

public:

	LetterFrequencyList();
	LetterFrequencyList(const LetterFrequencyList& Other);
	~LetterFrequencyList(); //destructor
	void copy(const LetterFrequencyList& Other);
	void destory();
	void insert(char ltr, size_t frq);
	void insertInOrder(char ltr);
	LetterFrequencyList& operator = (const LetterFrequencyList& Other);
	const string toString() const;
};


LetterFrequencyList::LetterFrequencyList() : HeadPtr(nullptr) {}

LetterFrequencyList::LetterFrequencyList(const LetterFrequencyList& Other) {
	copy(Other);
}
LetterFrequencyList::~LetterFrequencyList() {
	destory();
}

LetterFrequencyList::LetterNode* LetterFrequencyList::contains(char ltr) {

	LetterNode* temp = HeadPtr;
	while (temp != NULL) {
		if (temp->letter == ltr) {
			return temp;
		}
		temp = temp->Next;
	}
	return nullptr;
}

void LetterFrequencyList::copy(const LetterFrequencyList& Other) {
	LetterNode* temp = Other.HeadPtr;
	while (temp != NULL) {
		insert(temp->letter, temp->frequency);
		temp = temp->Next;
	}
}

void LetterFrequencyList::destory() {
	LetterNode* temp;
	while (HeadPtr != nullptr) {
		temp = HeadPtr->Next;
		delete HeadPtr;
		HeadPtr = temp;
	}
}


void LetterFrequencyList::insert(char ltr, size_t frq) {

	if (isalpha(ltr) == 0)
		return;                     // skip non alphabetical letters


	LetterNode* temp = contains(ltr); // uses the contains function to return walker or a nullptr

	if (temp != nullptr) {
		temp->frequency++;
	}
	else {
		HeadPtr = new LetterNode(ltr, frq, HeadPtr);
	}

}


void LetterFrequencyList::insertInOrder(char ltr) {
	/*1. If letter is NOT present in the linked list then it adds it as a LetterNode in such order
	that linked list stays sorted in ascending order(from front to back) at all times.
	Naturally when a letter node is being added for the first time, its frequency of
	occurrence is one.
	2. If letter node is already present in the list then function only increment its frequency
	field by one.*/

	if (isalpha(ltr) == 0) {
		return;                     // skip non alphabetical letters
	}

	ltr = toupper(ltr);


	if (HeadPtr == nullptr) {
		HeadPtr = new LetterNode(ltr, 1, HeadPtr); //creates a new node inside the list if there is none
	}
	else {

		LetterNode* temp = HeadPtr;   //temp is a copy of the object (HeadPtr), so we are able to modify temp
		temp = contains(ltr);

		if (temp != nullptr)
			temp->frequency++;
		else {

			temp = HeadPtr;
			LetterNode* temp2 = temp->Next;

			while (temp2 != nullptr) {

				if (temp2->letter > ltr) {
					temp->Next = new LetterNode(ltr, 1, temp2);
					return;
				}
				temp = temp->Next;
				temp2 = temp->Next;
			}

			temp->Next = new LetterNode(ltr, 1, nullptr);

		}
	}

}


LetterFrequencyList& LetterFrequencyList::operator = (const LetterFrequencyList& Other) {
	if (this != &Other) {
		destory();
		copy(Other);
	}
	return *this;
}

const string LetterFrequencyList::toString() const {
	string s = "";
	LetterNode* temp = HeadPtr;
	while (temp != nullptr) {
		s += temp->toString() + "\n";
		temp = temp->Next;
	}
	return s;
}

int main() {
	LetterFrequencyList List;
	string outputFileName = "";
	//Full path to file below:
	//"C:\Users\Owner\Desktop\C++\Visual Studio C++\TesFrequencyOfAllCharacters.txt"
	cout << "Enter full path to file : ";
	getline(cin, outputFileName);

	ifstream file;
	char input;
	file.open(outputFileName);
	if (!file.is_open()) {
		cout << "The path " << outputFileName << " may be invalid, or file reading not allowed." << endl;
		cout << "Try again." << endl;
	}
	else { //file opened successfully
		while (file >> input) {
			// cout << input << " ";
			if (input == 'b') {
				cout << " ";
			}
			List.insertInOrder(input);
		}
	}
	cout << endl << List.toString() << endl;
	file.close();
	system("pause");
	return 0;
}