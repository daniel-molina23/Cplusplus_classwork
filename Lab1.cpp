#include <iostream>
#include <string>
using namespace std;

int main(){

	string first;
	string last;
	cout << "Please Enter your first name: ";
	cin >> first;
	cout << "Please Enter your last name: ";
	cin >> last;

	int scores;     //input: test scores
	double sum = 0;	//output: total
	int inputCount = 0;     //total input counts
	
	// inputing grades
	cout << "Please enter your test scores, end of score entry must be indicated by a negative integer.\n";
	cout << "For example, if you took three tests and you scored 90, 91, 89 respectively, then you will enter\n";
	cout << "90 91 89 -5:\n";

	cin >> scores;
	cout << "\nYour name is                    : " << first << " " << last << "\n";
	if (scores < 0) {
		cout << first << " " << last << " you did not take any tests." << endl;
		return 0;
	}
	cout << "Your scores are                 : ";

	while (cin) {
		if (scores < 0) {
			break;
		}
		else {
			cout << scores << " ";
			sum += scores;
			cin >> scores;
			inputCount = inputCount + 1;
		}
	}
	cout << endl;
	
	double average;
	average = sum / inputCount;

	// char letterGrade;
	char grade;
		if (average > 90)
			grade = 'A';
		else if (average > 80 && average <= 90)
			grade = 'B';
		else if (average > 68 && average <= 80)
			grade = 'C';
		else if (average > 55 && average <= 68)
			grade = 'D';
		else
			grade = 'F';

	cout << first << " " << last << ", your average is "<< average;
	cout << " and your letter grade is " << grade << "." << endl;
	return 0;
}
