#include<iostream>

using namespace std;


/*template <class T>

class Bucky {
	T first;
	T second;
public:
	Bucky(T a, T b) {
		first = a;
		second = b;
	}
	T bigger();
};

template <class T>
T Bucky<T>::bigger() {
// the first T is the generic return type, and we use <T> because we need to tell Bucky's class that we are using the same template parameter "template <class T>"
// is the exact same template parameter well be using within the class
	return first > second ? first : second;
}*/

int main3() {

	//Bucky <int> bo(69, 105);

	//cout << bo.bigger() << endl;

	system("pause");
	return 0;
}



//template<class T> 
//
//class Spunky {
//public:
//	Spunky(T x) {
//		cout << x << " is not a character!" << endl;
//	}
//};
//
//template<>  //template specialization
//
//class Spunky <char> { //specializes in characters
//public:
//	Spunky(char x) {
//		cout << x << " is indeed a character!" << endl;
//	}
//
//};
//
//
//int main() {
//	Spunky <int> obj1(7);
//	Spunky <double> obj2(5.234);
//	Spunky <char> obj3('a');
//
//	system("pause");
//	return 0;
//}














//class Array {
//private:
//	int *dArray;
//	const int CAPACITY = 10;
//
//
//
//};


//int main() {
//
//	int a = 7;
//	int *p = NULL;
//	p = &a;
//
//	cout << *p << endl;
//
//
//
//	system("pause");
//	return 0;
//}









//const int CAPACITY = 10;
//
//int main() {
//
//	int *dArray;
//	dArray = new int[CAPACITY];
//
//	dArray[0] = 3;
//	dArray[1] = 7;
//	dArray[2] = 2;
//	dArray[3] = 9;
//	cout << "Enter an integer for your array" << endl;
//	int number;
//	cin >> number;
//	dArray.push_back(number);
//
//	cout << "Array: ";
//	for (int i = 0; i < 4;i++) {
//		cout << dArray[i] << " ";
//	}
//
//
//	delete[] dArray;
//	dArray = NULL;
//	system("pause");
//	return 0;
//}