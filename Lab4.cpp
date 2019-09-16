#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;


void FillNames(vector<string> & vecNames);
void SortNames(vector<string> & vecNames);

int main()
{

	vector<string> vecNames;

	FillNames(vecNames);
	SortNames(vecNames);
	system("pause");
	return 0;
}

void FillNames(vector<string> & vecNames)
{
	string nameInput;
	cout << "Information: " << endl;
	cout << "EOF character in windows is Control + Z\n"
		<< "and EOF character on Mac is Control + D\n"
		<< "-----------------------------------\n"
		<< endl;


	while (cin) {

		cout << "Enter first name only in all caps (example: JOHN)\n"
			<< "Enter EOF character to exit name entry: ";
		cin >> nameInput;
		vecNames.push_back(nameInput);
		cout << "-------------------------------------" << endl;
	}

}

void SortNames(vector<string> & vecNames) {

	cout << "The original names in the vector are:"
		<< endl;

	for (int i = 0; i < vecNames.size() - 1; i++) {

		cout << vecNames[i] << "  ";

	} // loop ends to output original names
	cout << endl;

	cout << "Organized:" << endl;
	int smallest = 0;

	for (int i = 0; i < vecNames.size() - 1; i++) {
		for (int m = i; m < vecNames.size() - 1; m++) {

			if (vecNames[m].compare(vecNames[smallest]) < 0) {
				smallest = m;
			}
		}
		if (smallest != i) {
			swap(vecNames[i], vecNames[smallest]);
		}
		cout << vecNames[i] << "  ";
	}
}
