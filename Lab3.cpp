#include<iostream>
#include<cmath>
#include<string>
using namespace std;

void BinaryToDecimal();
void OctalToDecimal();

int main()
{
	bool done = false;

	while (!false) {
		cout << "Caution! No validation is done on numbers entered."
			<< " They must conform to required input form.\n"
			<< "********* Main Menu *********\n"
			<< "1. Convert Binary to Decimal: \n"
			<< "2. Convert Octal to Decimal: \n"
			<< "3. Exit: " << endl;
		int choice;
		cin >> choice;

		if (choice == 1) {
			BinaryToDecimal();
		}
		else if (choice == 2) {
			OctalToDecimal();
		}
		else if (choice == 3) {
			done = true;
			break;
		}
		else {
			cout << "This choice is not yet implemented." << endl;
		}
	}
	return 0;
}

void BinaryToDecimal()
{

	string binNumber = "";
	int sum = 0;
	bool isValid;
	cout << "Enter the binary number: " << endl;
	cin >> binNumber;
	cout << "Original binary number: " << binNumber
		<< endl;

	for (int counter = 0; counter < binNumber.length(); counter++)
	{
		if (binNumber.at(counter) == '0' || binNumber.at(counter) == '1')
		{
			isValid = true;
		}
		else {
			cout << "This choice is not yet implemented. "
				<< "Please use 0 or 1 only." << endl;
			isValid = false;
			break;
		}

	}
	if (isValid == true) {
		for (int i = 0; i < binNumber.length(); i++) {
			const int number = (binNumber.at(i) - '0'); //Turns char to number
			sum += number * pow(2, binNumber.length() - 1 - i); //multiplies the number with 2^ (corresponding power 0,1,2 ... i)
		}
		cout << "Its decimal conversion: " << sum << endl;
	}
}


void OctalToDecimal()
{
	string octNumber = "";
	int sum = 0;
	bool isValid;
	cout << "Enter the octal number: " << endl;
	cin >> octNumber;
	cout << "Original octal number: " << octNumber
		<< endl;

	for (int counter = 0; counter < octNumber.length(); counter++)
	{
		if (octNumber.at(counter) != '8' && octNumber.at(counter) != '9')
		{
			isValid = true;
			//confirms octal numbers can only be 0 though 7 only
		}
		else {
			cout << "This choice is not yet implemented. "
				<< "Please use 0 through 7 only." << endl;
			isValid = false;
			break;
			// user input is incorrect and tells them to try again from main menu
		}

	}

	if (isValid == true) {
		// loop starts
		for (int i = 0; i < octNumber.length(); i++) {
			const int number = (octNumber.at(i) - '0'); //Turns char to integer
			sum += number * pow(8, octNumber.length() - 1 - i); //multiplies "number" with 8^ (corresponding power 0,1,2 ... i)
		}
		cout << "Its decimal conversion: " << sum << endl;
	}

}