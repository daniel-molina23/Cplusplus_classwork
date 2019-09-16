/*
Name: Daniel Molina
Class: CS52
Lab #: 9
Compiler Used: Visual Studio
Operating System Used: Windows 10
Date and Time of Last successful Compilation: 5/11/2019 3pm
Date and Time of when program verified all test results: 5/14/2019 3:35pm
*/

#include "BankAccount.h"
#include "ZeroOrNegativeInitialBalanceException.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<sstream>
#include<fstream>

using namespace std;
////////////////////*******FIRST MAIN FUNCTION*******////////////////////
//// T R I E S   A L L   O F   T H E   R E S U L T S    O U T    ////

int main() {
	try {
		BankAccount A1;
		BankAccount A2;
		cout << "object 1:" << endl;
		cout << A2.toString() << endl;
		A1.getInstance(A2);
		cin.ignore();
		cout << "object 2:" << endl;
		cout << A2.toString() << endl;
		A1.setAccountNumber("85745");
		cout << "Account Number: " << A1.getAccountNumber() << endl;
		
		cout << "Old Last Name:" << A1.getLastName() << endl;
		A1.setLastName("Don Charles");
		cout << "New Last Name: " << A1.getLastName() << endl;
		A2.withdraw(39.45);
		cout << "Balance after withdraw: $" << A1.getBalance() << endl;
		A2.deposit(220.91);
		cout << "Balance after deposit: $" << A1.getBalance() << endl;

		ofstream file;
		string outputFileName = "";
		cout << "Enter full path to output file : ";
		getline(cin, outputFileName);
		file.open(outputFileName);
		A2.print(file);
		file.close();
		A2.print();

		cout << "\nThe following was in the output file: " << endl;
		cout << "Account Number: " << A2.getAccountNumber() << endl;
		cout << "Full Name: " << A2.getFullName() << endl << endl;
		cout << "Balance: $" << A2.getBalance() << endl;
		cout << "--------------------" << endl;
		
		cout << endl << "Exception Handling is next....." << endl;

		ZeroOrNegativeInitialBalanceException EX1;
		cout << "Balance: $" << EX1.getInitBalance() << endl;
		cout << "Message: " << EX1.getMessage() << endl;
		ZeroOrNegativeInitialBalanceException EX2(22.22, "msg");
		cout << "Balance: $" << EX2.getInitBalance() << endl;
		cout << "Message: " << EX2.getMessage() << endl;
		
		BankAccount A3;
		ifstream infile;
		A3.getInstance(A3, infile);
	}
	catch (ZeroOrNegativeInitialBalanceException X) { // catches the exception
		cout << X.getMessage() << endl; 
	}
	catch (...) {
		cerr << "OOOPSIES. Error. Looks like you got an exception handle here. " << endl;
	}

	
	system("pause");
	return 0;
}





////////////////////*******SECOND MAIN FUNCTION*******////////////////////
          //// C O D E   F O R   T H E   M A I N   M E N U     ////


int main1() {
	bool menuCanProceed = false; //user can only access menu number 3-9 if menu # 1 or 2 is created
	int menu_selection = 0;
	BankAccount object;
	double bal = object.getBalance(); //regular balance
	string msg = ""; // exception message that will be thrown
	bool functionDone = false; //check to catch exceptions

	while (menu_selection == 0) {

		cout << "*************Main Menu*********************" << endl;
		cout << "1. Create an account from keyboard data entry" << endl
			<< "2. Create an account from input file data entry" << endl
			<< "3. Print account balance to console.[Must have $ sign and 2 digits in output]." << endl
			<< "4. Withdraw money" << endl
			<< "5. Deposit money" << endl
			<< "6. Print account details to console" << endl
			<< "7. Print account details to an output file." << endl
			<< "8. Print full name of account holder to console only." << endl
			<< "9. Print account number only of the account holder to console." << endl
			<< "10. Exit" << endl;
	
		cin >> menu_selection; //select a choice 
		
		if (menu_selection == 1) {//1. Create an account from keyboard data entry
		
			try {
				BankAccount::getInstance(object); //creates new instance	  

				menuCanProceed = true;

				menu_selection = 0; //main menu
			}
			catch (ZeroOrNegativeInitialBalanceException EX) {
				//catch exception
				cout << EX.getMessage() << endl;
			}
			
		}

		//else 
		if (menu_selection == 2) {//2. Create an account from input file data entry
			
			ifstream infile;
			//File Directory>>>>>>  C:\Users\Owner\Desktop\C++\Visual Studio C++\Laboratory_9\New_Account1.txt

			while (!functionDone) {
				try {
					cout << "Enter full directory to input file data entry: " << endl;
					string directory;
					cin.ignore();
					getline(cin, directory);

					infile.open(directory); //opens file of account information to access data

					if (infile.fail()) { //if file fails to open
						msg = "Error opening file. Please try again.";
						menuCanProceed = false; //instance never created, user cannot move on until successful creation of instance
						throw ZeroOrNegativeInitialBalanceException(bal, msg); //throwing to the catch block
					}
					else { //file opens successfully
						BankAccount::getInstance(object, infile); //defined in BankAccount.cpp
						functionDone = true;
						infile.close(); //close file
						menuCanProceed = true; //allows for the rest of the menu to be accessed

					}

					menu_selection = 0; //menu menu
				}
				catch (ZeroOrNegativeInitialBalanceException EX) {
					//catch exception
					cout << EX.getMessage() << endl;
					break; //exit loop
				}
			}
		}

		else if (menu_selection == 3) {//3. Print account balance to console.[Must have $ sign and 2 digits in output].
		
			if (menuCanProceed) {
				
				cout << "Current Balance: $" << fixed << setprecision(2) << object.getBalance() << endl; //outputs balance
			}
			else { //No Account has been created
				msg = "You must first create an account (1 or 2).";
				throw ZeroOrNegativeInitialBalanceException(bal, msg); //throwing to the catch block  
			}
			menu_selection = 0; //main menu
		}

		else if (menu_selection == 4) {//4. Withdraw money
			
			try {
				if (menuCanProceed) {

					cout << "Enter withdraw ammount [xx.yy]: $";
					double withdraw_money;
					cin >> withdraw_money;

					object.withdraw(withdraw_money); //defined in BankAccount.cpp
				}
				else { //No Account has been created

					msg = "You must first create an account (1 or 2).";
					throw ZeroOrNegativeInitialBalanceException(bal, msg); //throwing to the catch block  
				}
			}
			catch (ZeroOrNegativeInitialBalanceException EX) {
				//catch exception
				cout << EX.getMessage() << endl;
			}
			menu_selection = 0; //main menu
		}

		else if (menu_selection == 5) {//5. Deposit money
			try {
				if (menuCanProceed) {
					cout << "Enter deposit ammount [xx.yy]: $";
					double deposit_money;
					cin >> deposit_money;

					object.deposit(deposit_money); //defined in BankAccount.cpp
				}
				else { //No Account has been created
					msg = "You must first create an account (1 or 2).";
					throw ZeroOrNegativeInitialBalanceException(bal, msg); //throwing to the catch block  
				}
			}
			catch (ZeroOrNegativeInitialBalanceException EX) {
				//catch exception
				cout << EX.getMessage() << endl;
			}
			menu_selection = 0; //main menu
		}

		else if (menu_selection == 6) {//6. Print account details to console

			if (menuCanProceed) {

				object.print(); //outputs entire instance created
			}
			else { //No Account has been created
				msg = "You must first create an account (1 or 2).";
				throw ZeroOrNegativeInitialBalanceException(bal, msg); //throwing to the catch block  
			}
			menu_selection = 0; //main menu
		}

		else if (menu_selection == 7) {//7. Print account details to an output file.

			if (menuCanProceed) {

				cout << "What would you like to title your text file (example: file.txt): ";
				string filename;
				
				cin.ignore();
				getline(cin, filename); //gets entire directory
				
				ofstream outfile;
				outfile.open(filename); //opens inputted file

				if (outfile.bad()) { //file doesn't open successfully

					msg = "File was not created successfully. Try again";
					menuCanProceed = false; //file wasn't created
					throw ZeroOrNegativeInitialBalanceException(bal, msg); //throwing to the catch block  
				}
				else {
					cout << "Output file opening succeeded! All your data was saved in your inputed file directory." << endl;
					outfile << object.getAccountNumber() << endl
						<< object.getLastName() << endl
						<< object.getFirstName() << endl
						<< fixed << setprecision(2) << object.getBalance() << endl;

					outfile.close();

					cout << "Your file '" << filename << "' was created successfully." << endl;
				}
			}
			else { //No Account has been created
				msg = "You must first create an account (1 or 2).";
				throw ZeroOrNegativeInitialBalanceException(bal, msg); //throwing to the catch block  
			}
			menu_selection = 0; //main menu

		}

		else if (menu_selection == 8) {//8. Print full name of account holder to console only.
			if (menuCanProceed)
			{
				cout << "Name: " << object.getFullName() << endl
					<< "--------------------------------------" << endl;
				menu_selection = 0;
			}
			else { //No Account has been created
				msg = "You must first create an account (1 or 2).";
				throw ZeroOrNegativeInitialBalanceException(bal, msg); //throwing to the catch block  
				menu_selection = 0;
			}
		}

		else if (menu_selection == 9) {//9. Print account number only of the account holder to console.
			if (menuCanProceed) 
			{
				cout << "Account Number: " << object.getAccountNumber() << endl
					<< "--------------------------------------" << endl;
				menu_selection = 0;
			}
			else {//No Account has been created
				msg = "You must first create an account (1 or 2).";
				throw ZeroOrNegativeInitialBalanceException(bal, msg); //throwing to the catch block
				menu_selection = 0;
			}
		}

		else if (menu_selection == 10) {//10. Exit

			cout << "Program will now close . . ." << endl
				<< "Goodbye." << endl;
			
			break; //exit loop
		}

		else if (menu_selection > 10 || menu_selection < 0){
			cout << "That was an invalid entry. Please try again." << endl;
			menu_selection = 0;
		}

	}

	system("pause");
	return 0;
}
