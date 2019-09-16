/*
Name: Daniel Molina
Class: CS52
Lab #: 10
Compiler Used: Visual Studio
Operating System Used: Windows 10
Date and Time of Last successful Compilation: 5/19/2019 6:00pm
Date and Time of when program verified all test results: 5/21/2019 3:15pm
*/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cmath> //pow()

using namespace std;


template <typename T>
class StackInterface {


public:
	StackInterface() {};//constructor
	virtual ~StackInterface() {}; //destructor
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;
	virtual void push(T data) = 0;
	virtual void pop() = 0;
	virtual T top() = 0;
};

template<typename T>
class Stack {
private:
	T *items; 

//pointer stores address of dynamically created array of type T
	const static int MAX = 5; 
//initial capacity of dynamic array
	const static int GROWBY = 5;
/*When stack is filled and new push operation is attempted, the array used 
by the stack grows by additional capacity GROWBY and then push operation 
is completed*/

	size_t arrayCapacity; 
/*Array capacity at a particular time during program execution. At start
arrayCapacity = MAX, but it will increase, each time array grows by amount
GROWBY*/
	size_t numItems; 
//number of items added by the user to the stack
	int top_position;
/*Index managing the top of the stack. Starting value could be -1 or 
zero depending upon the implementation of push function.*/
public:
	Stack(); //constructor
	void push(T data);
/*Pushes data on to stack if numItems<arrayCapacity. Otherwise does the following:
2. Creates a dynamic array of size arrayCapacity + GROWBY
3. Copies elements from old stack to this new array (with increased capacity).
4. Adds data to stack.
5. Does required numItems and top_position adjustments.*/
	T top();
/*T top(); ------If stack is not empty, then returns ONLY a copy of the item on the top of stack.
Otherwise throws an exception using throw statement. You can write your own
exception class if you like, or use C++ exception class.*/
	void pop();
	bool isEmpty();
	bool isFull();
	size_t getArrayCapacity();
	size_t getNumItems();
	void copy(const Stack& st);
	const Stack& operator = (const Stack& st);
	~Stack();
	Stack(const Stack& st);
};

class EmptyStackException { //exception class
private:
	string message;
public:
	EmptyStackException(string msg = "Message not yet set")
		: message(msg) {}
	const string getMessage() const {
		return message;
	}
};

template<typename T>
Stack<T>::Stack() {
	items = new T[MAX];

	arrayCapacity = MAX;
	numItems = 0;
	top_position = -1; //set to either -1 or 0 depending on the push function
}

template<typename T>
void Stack<T>::push(T data) {
	T *temp = NULL; //initialize new array if used
	if (numItems < arrayCapacity) {
		items[numItems] = data; //input data into array
		numItems++; //number of items in array
		top_position++;
	}
	else { //numItems >= arrayCapacity
		arrayCapacity = arrayCapacity + GROWBY; //original array size + the amount the array should increase by
		T *temp = new T[arrayCapacity]; //create a bigger array
		for (unsigned int i = 0; i < numItems; i++) {
			temp[i] = items[i]; //copies values to the new array
		}
		delete[] items; //deallocate memory (prevents memory leak)
		items = NULL;
		items = temp; //'items' array now point to the new 'temp' array 
		items[numItems] = data; //input data into array
		numItems++; //number of items in array
		top_position++;
	}
}

template<typename T>
T Stack<T>::top(){
	T copy;
	T stack_exception;
	if (!isEmpty()){//'items' stack is not empty
		copy = items[top_position]; //copy of last item
	}
	else {
		string msg = "Error: The stack is empty.";
		throw EmptyStackException(msg);
	}
	return copy;
}

template<typename T>
void Stack<T>::pop() {
	if (isEmpty()) {
		cout << "Sorry your stack is empty, you cannot pop any items. Please add data." << endl;
	}
	top_position--; //reallocates the top element of stack 
	numItems--; //reallocates the number of Items in the stack
}

template<typename T>
bool Stack<T>::isEmpty() {
	bool emptyStack;
	if (numItems !=0) {//'items' stack is not empty
		emptyStack = false;

	}
	else {
		emptyStack = true;
	}
	return emptyStack;
}

template<typename T>
bool Stack<T>::isFull() {
	bool full;
	if (numItems == 0) {
		full = false;
	}
	else {
		full = true;
	}
	return full;
}

template<typename T>
size_t Stack<T>::getArrayCapacity() {
	return arrayCapacity;
}

template<typename T>
size_t Stack<T>::getNumItems() {
	return numItems;
}

template<typename T>
void Stack<T>::copy(const Stack& st) {
	
	if (items != NULL) {
		delete[] items;
	}
	numItems = st.numItems;
	top_position = st.top_position;
	arrayCapacity = st.arrayCapacity;
	T *copyArray = st.items;
	items = new T[arrayCapacity];
	for (unsigned int index = 0; index < numItems; index++) {
		items[index] = copyArray[index];
	}
}

template<typename T>
const Stack<T> & Stack<T>::operator = (const Stack<T>& st)
{
	if (this != &st) {//makes sure it doesn't copy the same 'st' object
		copy(st);
	}
	return *this;
}


template<typename T>
Stack<T>::~Stack() {
	if (items != NULL) {
		delete[] items;
	}
}

template<typename T>
Stack<T>::Stack(const Stack& st) {
	copy(st);
}

int main() {
	try {
		// ------------------------------------    Integer Testing    ------------------------------------
		cout << "************* Integer Testing *****************" << endl;
		cout << "Integer Stack called 'int_set' contains: ";
		Stack<int> int_set;
		int_set.push(0);
		int i = 1;
		while (int_set.isFull()) {
			int_set.push(i);
			cout << int_set.top() << "   ";
			if (i == 10) {
				break;
			}
			i++;
		}
		cout << endl << "Array Capacity: " << int_set.getArrayCapacity() << endl;
		cout << "Number of Items in Stack: " << int_set.getNumItems() << endl;


		cout << endl << "------------------------------" << endl;

		Stack<int> second_set(int_set); //copy constructor

		cout << "Int Stack'int_set' contains: " << endl;
		while (!int_set.isEmpty()) {
			cout << int_set.top() << endl;
			int_set.pop();
		}

		cout << endl << "------------------------------" << endl;

		cout << "'int_set' has been copied to Integer Stack 'second_set'.\nThe 'second_set' contains: ";

		int_set = second_set;

		while (!second_set.isEmpty()) {
			cout << second_set.top() << "   ";
			second_set.pop();
		}

		cout << endl << "Pop after stack is empty: ";

		second_set.pop(); //Exception!!!!!!

		cout << endl << "-----------------" << endl;
	}
	catch (EmptyStackException Exception) {
		cout << endl << "-----------------" << endl;
		cout << Exception.getMessage();
		cout << endl << "-----------------" << endl;
	}


	try{
	// ------------------------------------    Double Testing    ------------------------------------
	cout << endl << endl << "************* Double Testing *****************" << endl;
	Stack<double> dubl_set;
	Stack<double> second_dub;
	cout << "Object 'dubl_set' contains: ";

	double dub = 1.30;
	for (int i = 0; i < 10; i++) {
		dubl_set.push(dub);
		dub = dub + (2 * i - 1.01);
		cout << dubl_set.top() << "  ";
	}
	cout << endl << "-------------------------------" << endl;
	
	cout << "Second object 'second_dub' contains: ";
	double dood = 1.35;
	for (int i = 0; i < 10; i++) {
		second_dub.push(dood);
		dood = pow(1.4,dood);
		cout << second_dub.top() << "  ";
	}
	cout << endl << "-------------------------------" << endl;

	second_dub.copy(dubl_set);
	cout << "Now we just copied the 'dubl_set' into 'second_dub'." << endl
		<< "Unraveling the 'second_dub' stack, we get:" << endl;
	
	while (!second_dub.isEmpty()) {
		cout << second_dub.top() << "   ";
		second_dub.pop();
	}
	cout << "\nProgram for type <double> copying was successful!" << endl;


	cout << "\n----------------------------------------"
		<< "\nNow time to test characters!" << endl;

	}
	catch (EmptyStackException Exception) {
		cout << endl << "-----------------" << endl;
		cout << Exception.getMessage();
		cout << endl << "-----------------" << endl;
	}



	try{
	// ------------------------------------    Character Testing    ------------------------------------
	cout << endl << endl << "************* Character Testing *****************" << endl;
	Stack<char> char_set;
	Stack<char> second_char;

	cout << "\n'char_set' object contains: " << endl;
	char a;
	for (int j = 65; j < 80;j++) {
		a = char(j);
		char_set.push(a);
		cout << char_set.top()<<"   ";
	}
	cout << endl << "-------------------------------" << endl;

	cout << "'char_set' has been copied to Integer Stack 'second_char'.\n";

	second_char = char_set; //copy one object to another
	cout << "(Proof of copy)'second_char' contains: ";

	while(second_char.isFull()) {
		cout << second_char.top() << "   ";
		second_char.pop();
	}
	cout << endl << "-------------------------------" << endl;
	}
	catch (EmptyStackException Exception) {
		cout << endl << "-----------------" << endl;
		cout << Exception.getMessage();
		cout << endl << "-----------------" << endl;
	}


	try{
	// ------------------------------------    String Testing    ------------------------------------

	cout << endl << endl << "************* String Testing *****************" << endl;
	Stack<string>first_string;
	cout << "'first_string' array capacity: " << first_string.getArrayCapacity() << endl;
	cout << "Number of items: " << first_string.getNumItems() << endl;

	string input = "loo ";
	for (int i = 0; i < 10; i++) {
		input = "la " + input;
		first_string.push(input);
		cout << first_string.top() <<"   ";
	}
	cout << endl << "-------------------------------" << endl;
	cout << "New capacity of 'first_string': " << first_string.getArrayCapacity() << endl;
	cout << "Number of items: " << first_string.getNumItems() << endl;

	for (int i = 0; i < 9; i++) { // pop from stingObj
		first_string.pop();
		cout << "New top after pop: " << first_string.top() << endl;
	}
	}
	catch (EmptyStackException Exception) {
		cout << endl << "-----------------" << endl;
		cout << Exception.getMessage();
		cout << endl << "-----------------" << endl;
	}

	system("pause");
	return 0;
}