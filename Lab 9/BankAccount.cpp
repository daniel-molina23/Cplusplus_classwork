
#include "BankAccount.h"
#include "ZeroOrNegativeInitialBalanceException.h"

BankAccount::BankAccount() {
	ActNum = "Account number not set";
	LastName = "Last Name not set";
	FirstName = "First Name not set";
	balance = 0.0;
}

BankAccount::BankAccount(const string & actN, const string & fname, const string & lname, double bal) {
	ActNum = actN;
	FirstName = fname;
	LastName= lname;
	balance = bal;
}

void BankAccount::deposit(double money) {
	//deposited from main()
	string msg = "";
	
	if (money > 0) {//checks if non-zero and positive
		balance += money;
		cout << "Transaction was successfull!" << endl
			<< "New Balance is: $" << getBalance() << endl;
	}
	else if (money == 0) {
		msg = "Deposit was not successful!\nYou are not able to deposit zero dollars. You have no balance difference."; //NO balance update
		throw ZeroOrNegativeInitialBalanceException(balance, msg); //throwing to the catch block in the main
	}
	else { //negative money
		msg = "Error: depositing negative dollars is not allowed."; //NO balance update
		throw ZeroOrNegativeInitialBalanceException(balance, msg); //throwing to the catch block in the main
	}
}

string BankAccount::getAccountNumber() const {
	return ActNum;
}
double BankAccount::getBalance() const {
	return balance;
}
const string BankAccount::getFirstName() const {
	return FirstName;
}
const string BankAccount::getLastName() const {
	return LastName;
}
const string BankAccount::getFullName() const {
	return FirstName + " " + LastName;
}
void BankAccount::setAccountNumber(const string & actN) {
	ActNum = actN; //sets to a new Account Number
}
void BankAccount::setLastName(const string & lname) {
	LastName = lname; //sets to a new Last Name
}
const string BankAccount::toString() const {
	ostringstream bar;
	
	bar << "Bank Account object created:\n" << endl
		<< "Account Number: " << getAccountNumber()
		<< "    Name: " << getFullName()
		<< "    Balance: $" << fixed << setprecision(2) //2 decimal places
		<< getBalance() << endl;
	return bar.str();
}

void BankAccount::withdraw(double money) {
	if (money > balance) {
		string msg = "Error: You do not have enough funds to take out that amount of money.";
		throw ZeroOrNegativeInitialBalanceException(balance, msg); //throwing to the catch block in the main
	}
	else if (money == balance) {
		string msg = "You're broke, you have no more money. New account balance is zero.";
		throw ZeroOrNegativeInitialBalanceException(balance, msg); //throwing to the catch block in the main
	} //should this be thrown?^^^
	else if (money == 0) {
		string msg = "You cannot withdraw zero dollars from your account. Transaction was not successful.";
		throw ZeroOrNegativeInitialBalanceException(balance, msg); //throwing to the catch block in the main
	}
	else {
		
		if (money < 0) { //negative value

			string msg = "Error: You cannot withdraw a negative amount. Try again.";
			throw ZeroOrNegativeInitialBalanceException(balance, msg); //throwing to the catch block in the main
		}
		else { //positive money will be withdrawn
			balance -= money;
			cout << "Transaction was successfull!" << endl
				<< "New Balance is: $" << getBalance() << endl;
		}
	}
}

void BankAccount::print(ostream & out) const {
	
	out << "Account Number: " << getAccountNumber() << endl
		<< "Name: " << getFullName() << endl
		<< "Balance: $" << fixed << setprecision(2) //2 decimal places
		<< getBalance() << endl;
}

void BankAccount::getInstance(BankAccount & BA) {

	cout<<"Enter the balance or initial deposit [xx.yy] : $"; 
	cin>>BA.balance;
	 
	if (BA.balance == 0 ) {
		string msg = "Initial balance of zero dollars is insufficient.";
		throw ZeroOrNegativeInitialBalanceException(0.0, msg);
	}
	else if(BA.balance < 0){
		string msg = "Initial balance of negative dollars is not allowed.";
		throw ZeroOrNegativeInitialBalanceException(0.0, msg);
	}

	cout << "Enter the new (unique) account number: ";
	cin >> BA.ActNum;
	cout << "Enter the first name on account: ";  
	cin >> BA.FirstName; 
	cout << "Enter the last name on account: "; 
	cin >> BA.LastName;
}

void BankAccount::getInstance(BankAccount & BA, ifstream & in) {

	string account;
	getline(in, account); //takes the first line from the file
	
	string lastname;
	getline(in, lastname); //takes the second line from the file

	string firstname;
	getline(in, firstname); //takes the third line from the file

	string balance;
	getline(in, balance); //takes the fourth line from the file
	double balAmount = stod(balance); //converts from string to double

	BA = BankAccount(account, firstname, lastname, balAmount); //creates a new Bank Account instance from a file directory

}