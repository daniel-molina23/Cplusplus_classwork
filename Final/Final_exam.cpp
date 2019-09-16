/*
Name: Daniel Molina
Class: CS52
Exam : Final Exam
Compiler Used: Visual Studio
Operating System Used: Windows 10
Date and Time of Last successful Compilation: 6/1/2019 10am
Date and Time of when program verified all test results: 6/2/2019 8:57pm
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct PolyNode {
	int coefficient;
	int power;
	PolyNode * Next;

	PolyNode(int c = 1, int pwr = 0, PolyNode * ptr = nullptr) : coefficient(c), power(pwr), Next(ptr)
	{ }
	
	const string toString() const {
		return to_string(this->coefficient) + "X^" + to_string(this->power);//converted values to string
	}
};

struct PolyLinkedList {
	PolyNode * HeadPtr;

	PolyLinkedList() : HeadPtr(new PolyNode('A', 'B', nullptr)) { } //constructor

	/*
	1. Write a copy function that would be called from
		inside of copy constructor and assignment operator to make
		deep copy of PolyLinkedList PLL into the current object.*/
	void copy(const PolyLinkedList & PLL) {
		destroy();//must clear self before copying
		if (PLL.HeadPtr == nullptr) {
			HeadPtr = nullptr;
		}
		else {
			PolyNode *C = HeadPtr;
			PolyNode *I = PLL.HeadPtr->Next;
			while (I != nullptr) {
				C->Next = new PolyNode(I->coefficient, I->power, nullptr);
				I = I->Next;
				C = C->Next;
			}
		}
	}

	/*
	2. Write a destroy function that is called from inside of destructor body
		and from inside of assignment operator to de-allocate the dynamically allocated memory
		for linked list nodes. The destroy function and its correct use,
		eliminates the possibility of memory leaks in a linked list application. */
	void destroy() {
		if (HeadPtr == nullptr) return;
		PolyNode * Current = HeadPtr->Next;//starts with dummy node
		while (Current != nullptr) {//deletes the individual linked lists until it reaches the end
			PolyNode *save = Current;
			Current = Current->Next;
			delete save;
			save = nullptr;
		}
		HeadPtr->Next = nullptr;
	}

	//Enforcement of Rule of three
/*
3. Write a copy constructor that makes deep copies
	when a PolyLinkedList object is passed by value to a function
	or is returned by a function as a return value.
	The copy constructor disallows self-copy.
	For example, if client tries to write a code such as below,
	the program warns that self-copy is not allowed and program exits.
PolyLinkedList P;
PolyLinkedList Q(P);
copy function written as item 1 above should be called from within the body of copy constructor below.
*/
	PolyLinkedList(const PolyLinkedList & OtherPoly) {
		
		cout << "From copy constructor.\n"; 
		if (this == &OtherPoly) { //can't copy itself
			assert(("Self copying is not allowed in the program. Program will now exit.", this == &OtherPoly));
		}
		HeadPtr = new PolyNode('A', 'B', nullptr);
		copy(OtherPoly);//copy function
	}

	/*4. Write the body of assignment operator that
		makes a deep copy when the PolyLinkedList OtherPoly is copied into another object using the assignment operator (=).
		The code inside assignment operator also should handle the situation when user attempts a code such as below:
			PolyLinkedList P;
			P = P;
		The destroy and copy function must be used . */
	const PolyLinkedList & operator = (const PolyLinkedList & OtherPoly) {
		
		cout << "From assignment operator!" << endl;
		if (this != &OtherPoly) { 
			destroy(); //delete memory from the left side
			copy(OtherPoly);
			cout << "Object has successfully copied!" << endl;
		}
		else { //can't copy itself
			cout << "Error, object cannot copy itself" << endl;
		}
		return *this;//return a pointer to the built current object
	}

	/*
	5. Destructor simply calls the destroy function coded as item 2 to de-allocate dynamically allocated nodes of linked list.
		This will just be one line of code, because function destroy does all the heavy lifting.*/
	virtual ~PolyLinkedList() {
		destroy();
	}

	/*
	6. The function insertInOrder inserts nodes into PolyLinkedList
		such that nodes are inserted from front to back in the order of decreasing power of X,
		with last node being the constant. Please see the Figure 1 as to how final linked list would look like even if the nodes were inserted in a random order.
		For example, user may choose to insert constant first, and then some power of X etc.
		In other words, the linked list generated would look like picture in Figure 1, even if code as below was executed.
	PolyLinkedList PLL;
	PLL.insertInOrder(1, 0);
	PLL.insertInOrder(4, 3);
	PLL.insertInOrder(2, 1);
	PLL.insertInOrder(3, 2);
	Additional requirement is that two nodes with the same value of the power field are not allowed.
	For example, if user attempts to insert another node to PLL as below,
	user is informed that node already exits and such node is not added.
	PLL.insertInOrder(9,3); */

	void insertInOrder(int c, int pwr) {// c is coefficient and pwr is power

		PolyNode *Current = HeadPtr;
		
		if (Current->Next == nullptr) { //list is empty, therefore add new instance
			cout << "List was empty, polynomial " << c << "X^" << pwr << " has been successfully added." << endl;
			Current->Next = new PolyNode(c, pwr, nullptr);
		}
		else {//Polynomial not empty, therefore sort

			while (Current->Next != nullptr) {//iterate through the list
				
				if (Current->Next->power < pwr) {//it is smaller than the node trying to be placed in the list
					PolyNode *add = new PolyNode(c, pwr, HeadPtr->Next);
					add->Next = Current->Next;
					Current->Next = add;
					cout << "node of " << c << "*X^(" << pwr << ") is inserted in order" << endl;
					break;  //break while loop
				}
				else if (Current->Next->power == pwr) {
					cout << "Error, you cannot have a polynomial with the same power of X^" << pwr << endl;
					cout << "Node wasn't added to list." << endl;
					break;
				}
				//Go to next node
				Current = Current->Next;
				if (Current->Next == nullptr) {//insert node at the end of the list
					PolyNode *add = new PolyNode(c, pwr, Current->Next);
					Current->Next = add;
					cout << "Polynomial " << c << "X^" << pwr << " has been succesully added at the end of the list" << endl;
					break;
				}
			}
		}
	}


	/*
	7. The function insertFront adds the node with coefficient C and power pwr as the first significant node after the dummy node,
		only if sorted order of the linked list (descending order of power of X) is NOT disturbed,
		or Linked list has no nodes in it. If adding the node in front of the list is attempted and it disturbs the sorted order of the list,
		then node is NOT added and user is informed about it’s not being added. */
	void insertFront(int c, int pwr) {
		PolyNode *Check = HeadPtr->Next;

		if (HeadPtr->Next == nullptr) {
			HeadPtr->Next = new PolyNode(c, pwr, nullptr);
			cout << "Polynomial " << c << "X^" << pwr << " was successfully placed in front of the list." << endl;
		}
		else if (Check->power < pwr){// if (HeadPtr->Next != nullptr)
			HeadPtr->Next = new PolyNode(c, pwr, HeadPtr->Next);
			cout << "Polynomial " << c << "X^" << pwr << " was successfully placed in front of the list." << endl;
		}
		else if (Check->power > pwr) { //distrubs order
			cout << "Sorry, node was not added because it disturbs the order of the polynomial.\n";
			cout << "Your polynomial order must be larger than X^" << Check->power << " to insert in front of the list." << endl;
		}
		else if (Check->power == pwr) {
			cout << "You cannot add polynomials of the same order (or same power) to the list\n";
		}
	}
	/*
	8. The function insertTail adds the node with coefficient C and power pwr as the last significant node in the linked list,
		only if sorted order of the linked list (descending order of power of X) is NOT disturbed,
		or Linked list has no nodes in it.
		If adding the node as the last node in the list is attempted and it disturbs the sorted order of the list,
		then node is NOT added and user is informed about it’s not being added. */
	void insertTail(int c, int pwr) {
		PolyNode *Check = HeadPtr->Next;

		if (Check == nullptr) {//list is empty
			HeadPtr->Next = new PolyNode(c, pwr, nullptr);
			cout << "Polynomial " << c << "X^" << pwr << " was successfully placed at the end of the list." << endl;
		}
		else { //list not empty
			while (Check->Next != nullptr) {//iterate through the entire list before reaching the nullpointer
				Check = Check->Next;
			}

			if (Check->power > pwr) {//has to be smaller polynomial than the one before
				Check->Next = new PolyNode(c, pwr, nullptr);
				cout << "Polynomial " << c << "X^" << pwr << " was successfully placed at the end of the list." << endl;
			}
			else if (Check->power < pwr) { //distrubs order
				cout << "Sorry, node was not added because it disturbs the order of the polynomial.\n";
				cout << "Your polynomial order must be smaller than X^" << Check->power << " to insert at the end of the list." << endl;
			}
			else {//Check->power == pwr
				cout << "You cannot add polynomials of the same order (or same power) to the list\n";
			}
		}
	}

	/*
	9. Write the function getSize, that would iterate through the linked list
		and get ONLY number of significant nodes in the linked list
		and ignores dummy node from this count.
		For example, if linked list has only dummy node, getSize will return 0. \
		Otherwise it will return number of polynomial nodes in the linked list */
	size_t getSize() const {
		PolyNode *i;
		unsigned int size = 0; //count the size of linked list
		for (i = HeadPtr->Next; i != nullptr; i = i->Next) {
			if (i == nullptr) {//exits loop if list is empty, size = 0
				break;
			}
			size++;
		}
		return size;
	}

	/*
	10. Function getValue returns the integer number that results from substituting arg for X in the linked list.
	Examples are shown in table below: */
	int getValue(int arg) {
		PolyNode *Instance = HeadPtr->Next;
		int totalValue = 0;
		while (Instance!=nullptr) {
			totalValue += (int)(Instance->coefficient)*pow(arg,(Instance->power));
			Instance = Instance->Next;
		}
		return totalValue;
	}

	/*
	11. Write the friend function operator == that returns true
	if both linked lists left and right are identical in content of all nodes,
	or returns false otherwise. */

	friend bool operator == (const PolyLinkedList & left, const  PolyLinkedList & right) {
		bool checkifequal = false;
		PolyNode *p = left.HeadPtr, *g = right.HeadPtr;
		while (p->Next != nullptr || g->Next != nullptr) {
			p = p->Next;
			g = g->Next;
			if (p->coefficient == g->coefficient && p->power == g->power) {
				checkifequal = true;
			}
			else {//not equal nodes
				checkifequal = false;
				break; //exit loop
			}
		}
		return checkifequal;
	}

	friend ostream& operator <<(ostream& out, const PolyLinkedList& list) {
		out << list.toString() << endl;
		return out;
	}

	const string toString() const {
			
			PolyNode* Iterator = HeadPtr->Next;
			string list = "";

			while (Iterator != nullptr) { //loop until the end
				list = list + Iterator->toString(); // toString function from PolyNode struct 
				if (Iterator->Next != nullptr) list += " + ";
				Iterator = Iterator->Next;
			}
			return list;
	}

};// End of struct PolyLinkedList

/*
11. Write code in main function that you used to test your code as you went through the incrementally developing the various PolyLinkedList functions.
	Document the output of each test, either in cpp file or in a Microsoft word file.
	Test should be clear enough that if I wish to try that test, I should be able to do it.
	After finishing all tests, rename this function as Test*/


void Test() {

	cout << "Using the insertFront for object 1 . . ." << endl;
	PolyLinkedList obj1;
	PolyLinkedList obj2;

	obj1.insertFront(1, 2);
	obj1.insertFront(3, 3);
	obj1.insertFront(2, 4);
	obj1.insertFront(3, 3);//cant be inserted in front
	obj1.insertFront(1, 4);//cant insert the same node
	cout << "The whole polynomial for object 1: " << obj1 << endl; //overloading << operator
	cout << "-----------------" << endl;

	obj2 = obj2;//cant copy itself
	obj2 = obj1;

	cout << "Object 2 contains: " << obj2 << endl << endl; //overloading << operator
	
	obj1.destroy();
	cout << "Object 1 has been destroyed." << endl << endl;

	cout << "Using the insertTail for object 2 . . ." << endl;
	obj2.insertTail(4, 1);
	obj2.insertTail(9, 0);
	obj2.insertTail(9, 3); //cannot  be entered, same power
	obj2.insertTail(9, 6); //cannot  be entered

	cout << "Object 2 now contains: " << obj2 << endl << endl;

	PolyLinkedList obj4(obj2);//copy  constructor

	cout << "Testing == bool function. If '1' they are equal, '0' if not." << endl;
	cout << (obj4 == obj2) << endl; //TRUE
	cout << "----------------" << endl << endl;

	obj1.insertTail(3, 3);

	cout << "Testing == bool function. If '1' they are equal, '0' if not." << endl;
	cout << "(Object 1{3X^3} vs. Object 2)" << endl;
	cout << (obj1 == obj2) << endl; //FALSE
	cout << "----------------" << endl;

	PolyLinkedList obj3;
	obj3.insertInOrder(1, 8);
	obj3.insertInOrder(2, 9);
	obj3.insertInOrder(3, 6);
	obj3.insertInOrder(4, 3);

	cout << "Object 3 contains: " << obj3 << endl << endl; //overloading << operator

	cout << "Size of object 3: " << obj3.getSize() << endl<<endl;

	cout << "Entering the value of (6) into object 3, we get: " << obj3.getValue(6) << endl;
	cout << "Entering the value of (-4) into object 3, we get: " << obj3.getValue(-4) << endl;
	cout << "Entering the value of (0) into object 3, we get: " << obj3.getValue(0) << endl << endl;

/*	PolyLinkedList P;
	PolyLinkedList Q(P);*///impossible, compile error, cannot do this

	cout << "\nNew object (#9) has been created." << endl;
	PolyLinkedList obj9;
	obj9.insertInOrder(7, 0);
	obj9.insertInOrder(1, 7);
	obj9.insertInOrder(5, 3);
	obj9.insertInOrder(8, 4);
	cout << "Object 9 contains the polynomial: "<<obj9 << endl << endl;

	cout << "Object 9 will now be copied into Object Q, Q now contains:" << endl;
	PolyLinkedList Q(obj9);
	cout << Q << endl << endl;

}


	/*
	12. Final main function: (Use and code helper stand-alone functions as needed)
		1. Declare a vector of PolyLinkedList before the loop. Assume that vector is called PolyVec
		2. Have a loop menu driven program in the main function with following menu items.
		1.	Add Polynomials to PolyVec from keyboard data entry. This menu item should allow user to add as many polynomials to the PolyVec as user desires. This menu item should first prepare a polynomial using insertInOrder function and then use push_back to add to the PolyVec. Make sure that two of the added polynomials are identical, so that we can test == operator.
		2.	Print all polynomials to the console.
		3.	Print all polynomials to an output file. User must be able to specify the full path to the output file and validation that file is successfully opened for writing is required. Understand that full path to file may have white spaces.
		4.	Print to console values of all polynomials when X = 1, X = 2, X = 5. See table we have done for the getValue function.
		5.	Test == operator for those two polynomials in PolyVec, that are identical in content.
		6.	Print to console, the number of terms (using getSize function) for ll polynomials in PolyVec.
		7.	Repeat the test you did for testing function insertFront
		8.	Repeat the test you did for testing function insertTail
		9.	Exit

		Provide tables for all the data you used to test all menu items above. */


int main() {
	bool inputedValues = false;//values have been inputted to Menu == 1

	int Menu = 0; //goes to main menu
	vector<PolyLinkedList> PolyVec;
	while (Menu == 0) {
		cout << "************ Main Menu***************\n"
			<< "1. Add Polynomials to PolyVec from keyboard data entry.\n"
			<< "2. Print all polynomials to the console.\n"
			<< "3. Print all polynomials to an output file.\n"
			<< "4. Print to console values of all polynomials when X = 1, X = 2, X = 5.\n"
			<< "5. Test == operator for those two polynomials in PolyVec, that are identical in content.\n"
			<< "6. Print to console, the number of terms (using getSize function) for ll polynomials in PolyVec.\n"
			<< "7. Repeat the test you did for testing function insertFront\n"
			<< "8. Repeat the test you did for testing function insertTail\n"
			<< "9. Exit" << endl;
		cin >> Menu;
		cin.ignore();

		if (Menu == 1) {
			int input = -1;
			bool Done = false;
			int coefficient;
			int power;
			PolyLinkedList object;

			while (!Done) {
				cout << "Insert Polynomial's coefficient : ";
				cin >> coefficient;
				cout << "Insert Polynomial's power : ";
				cin >> power;
				//cout << coefficient << endl;
				object.insertInOrder(coefficient, power);
				cout << "Enter 1 if you're done entering polynomials, press 0 if you would like to insert more terms into the Polynomial :";
				cin >> input;
				cout << endl;
				//if (Done) {//uses copy constructors
				//	PolyVec.push_back(object); //vector stores copy of the object
				//	cout << "Polynomial : " << object << " is added to PolyVec" << endl;
				//}
				if (input != 1 && input != 0) {
					//PolyVec.push_back(object); //vector stores copy of the object
					//object.destroy();
					cerr << "That was an invalid input, please try again." << endl;
					break;
				}
				else if (input == 1) {
					Done = true;
				}
				if (Done) {
					inputedValues = true; //values have been stored, you may use Menu == 2,3,4 or 6
					PolyVec.push_back(object); //vector stores copy of the object
					cout << "Polynomial : " << object << " is added to PolyVec" << endl;
				}
			}
			Menu = 0; //go to main menu
		}

		else if (Menu == 2 && inputedValues) { // Prints all polynomials
			for (unsigned int i = 0; i < PolyVec.size(); i++) {
				cout << "Polynomial #" << i + 1 << ": " << PolyVec[i].toString() << endl;
			}
			Menu = 0; //go to main menu
		}

		else if (Menu == 3 && inputedValues) { //Print all polynomials to an output file 
			ofstream file;
			string outputFileName = "";
			cout << "Enter full path to output file : ";
			getline(cin, outputFileName);
			file.open(outputFileName); // opens 'outputFileName'

			if (file.is_open()) { // if file is open
				cout << "Output file opened successfully." << endl;

				for (unsigned int i = 0; i < PolyVec.size(); i++) { // storing all data to file
					file << PolyVec[i].toString() << endl;//writing to file
					cout << PolyVec[i] << endl;
				}

				cout << "Information was stored in file: " << outputFileName << endl;
				file.close(); // closes 'outputFileName'
				cout << "Output file successfully closed." << endl;
			}
			else { // file didn't open correctly
				cout << "File opening failed, invalid path to output file, please try again." << endl;
				file.close();
			}
			Menu = 0; //go to main menu
		}

		else if (Menu == 4 && inputedValues) { //Print to console values of all polynomials when X = 1, X = 2, X = 5.
			for (unsigned int i = 0; i < PolyVec.size(); i++) {
				cout << "For polynomial : " << PolyVec[i].toString() << endl
					<< "For X = 1, value = " << PolyVec[i].getValue(1) << endl
					<< "For X = 2, value = " << PolyVec[i].getValue(2) << endl
					<< "For X = 5, value = " << PolyVec[i].getValue(5) << endl << endl;
			}
			Menu = 0; //go to main menu
		}

		else if (Menu == 5 && inputedValues) { //Test == operator for those two polynomials in PolyVec, that are identical in content.
			if (PolyVec.size() == 1) {
				cout << "You need to input a second object to compare it with. Try Again." << endl;
			}
			else {
				cout << "Comparing the 1st and 2nd polynomials in PolyVec below." << endl
					<< "> If it prints '1' they are identical and if '0' they are not identical : ";
				cout << (PolyVec[0] == PolyVec[1]) << endl;
			}
			Menu = 0; //go to main menu
		}

		else if (Menu == 6 && inputedValues) { //Print to console, the number of terms (using getSize function) for ll polynomials in PolyVec
			for (unsigned int i = 0; i < PolyVec.size(); i++) {
				cout << "The polynomial : " << PolyVec[i].toString() << " has '" << PolyVec[i].getSize() << "' term(s)." << endl;
			}
			Menu = 0; //go to main menu
		}

		else if (Menu == 7) { //Repeat the test you did for testing function insertFront
			cout << endl << "Testing the function insertFront . . .\n" << endl;
			PolyLinkedList object;
			object.insertFront(2, 2);
			cout << "the new polynomial is : " << object << endl;
			object.insertFront(3, 3);
			cout << "the new polynomial is : " << object << endl;
			object.insertFront(4, 4);
			cout << "the new polynomial is : " << object << endl;
			object.insertFront(8, 8);
			cout << "the new polynomial is : " << object << endl;
			object.insertFront(1, 8); // X^8   ******** cannot be inserted , same power exists
			cout << "the new polynomial is : " << object << endl;
			object.insertFront(2, 7); // 2*X^7 ******** cannot be inserted , b/c it messes up the order of the list
			cout << "the new polynomial is : " << object << endl << endl;

			cout << ".  .  . done tesing." << endl;
			Menu = 0; //go to main menu
		}

		else if (Menu == 8) { //Repeat the test you did for testing function insertTail
			cout << endl << "Testing the function insertTail . . .\n" << endl;

			PolyLinkedList object;
			object.insertTail(6, 6);
			cout << "the new polynomial is : " << object << endl;
			object.insertTail(2, 6);// 2X^6   ******** cannot be inserted , same power exists
			cout << "the new polynomial is : " << object << endl;
			object.insertTail(5, 5);
			cout << "the new polynomial is : " << object << endl;
			object.insertTail(3, 3);
			cout << "the new polynomial is : " << object << endl;
			object.insertTail(2, 4);// 2*X^4 ******** cannot be inserted , b/c it messes up the order of the list
			cout << "the new polynomial is : " << object << endl;
			object.insertTail(2, 2);
			cout << "the new polynomial is : " << object << endl;
			object.insertTail(1, 0); // constant (1X^0 or 1)
			cout << "the new polynomial is : " << object << endl << endl;

			cout << ".  .  . done tesing." << endl;
			Menu = 0; //go to main menu
		}

		else if (Menu == 9) { // exits program
			cout << "Exiting Program. Bye, Bye. See yah!" << endl;
			break;
		}
		else { // invalid entree
			if (!inputedValues) {
				cout << "You cannot use that function, you need to first input values in the object for Menu == 1" << endl;
			}
			else {
				cout << "\nThat was an invalid entree, please enter a number from  1 through 9." << endl << endl;
			}
			Menu = 0; //go to main menu
		}
	}
	Test();//tests the hardcoded function in void Test();
	system("pause");
	return 0;
}