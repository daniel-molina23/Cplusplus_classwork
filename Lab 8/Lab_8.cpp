/*
Student Name : Daniel Molina
Project Name : CS52 Lab8 -> Inheritance from Abstract Class(es)
Start Date : May 1st, 2019
Completion Date : May 4th, 2019
Operating System Used : Windows 10
Compiler Used : Visual Studio
Student Email : molina_daniel_eduard@student.smc.edu
*/

#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include "Employee.h" //base class
#include "Manager.h" //derived class

using namespace std;


int main() {

	string firstname = "";
	string lastname = "";
	string title = "";
	double salary = 0.0;

	string NewLastname = "";
	string NewBossTitle = "";
	double NewSalary = 0.0;

	bool check_running = false;
	int Menu = 0;
	Manager obj;

	while (Menu == 0) {


		cout << "**************** Main Menu****************" << endl;
		cout << "Enter the menu item of choice and press enter key." << endl;
		cout << "1. Create Manager instance from keyboard:" << endl
			<< "2. Print Manager to Console." << endl
			<< "3. Change Manager's last name." << endl
			<< "4. Change Manager's Salary." << endl
			<< "5. Change Manager's Boss'es Title." << endl
			<< "6. Print only Manager's name and Salary to console." << endl
			<< "7. Print only Manager's boss'es title to console." << endl
			<< "8. Exit" << endl;

		cin >> Menu;//Menu input

		if (Menu == 1) { // 1. Create Manager instance from keyboard

			cout << "Enter first name of Manager: ";
			cin >> firstname;

			cout << "Enter last name of Manager: ";
			cin >> lastname;

			cout << "Enter title of Manager's Boss: ";
			cin >> title;

			cout << "Enter Manager's salary [xx.yy]: ";
			cin >> salary;

			obj.setFirstName(firstname);
			obj.setLastName(lastname);
			obj.setBossTitle(title);
			obj.setSalary(salary);

			check_running = true; // menu 1 ran correctly

			Menu = 0; // returns to main menu (re-select)
		}

		else if (Menu == 2) { // 2. Print Manager to Console.

			if (check_running) {
				cout << obj.toString();
			}

			else { // manager instance has not been created
				cout << "Please create a Manager instance using option 1 before using this option." << endl;
				cout << "------------------------------------------------" << endl;
			}

			Menu = 0; // returns to main menu (re-select)
		}

		else if (Menu == 3) { // 3. Change Manager's last name.

			if (check_running) {
				cout << "Enter Manager's new last name: ";
				cin >> NewLastname;
				obj.setLastName(NewLastname);
				cout << "------------------------------------------------" << endl;
			}

			else { // manager instance has not been created
				cout << "Please create a Manager instance using option 1 before using this option." << endl;
				cout << "------------------------------------------------" << endl;
			}

			Menu = 0; // returns to main menu (re-select)
		}

		else if (Menu == 4) { // 4. Change Manager's Salary

			if (check_running) {
				cout << "Type manager's new salary and press enter key: $";
				cin >> NewSalary;
				obj.setSalary(NewSalary);
				cout << "------------------------------------------------" << endl;
			}
			else { // manager instance has not been created
				cout << "Please create a Manager instance using option 1 before using this option." << endl;
			}

			Menu = 0; // returns to main menu (re-select)
		}

		else if (Menu == 5) { // 5. Change Manager's Boss'es Title

			if (check_running) {
				cout << "Enter Manager's Boss'es new Title: ";
				cin >> NewBossTitle;
				obj.setBossTitle(NewBossTitle);
				cout << "------------------------------------------------" << endl;
			}

			else { // manager instance has not been created
				cout << "Please create a Manager instance using option 1 before using this option." << endl;
			}

			Menu = 0; // returns to main menu (re-select)
		}

		else if (Menu == 6) { // 6. Print only Manager's name and Salary to console
			cout << "Manager's Name: " << obj.getFullName() << endl;
			cout << "Salary: $" << obj.getSalary() << endl;
			cout << "------------------------------------------------" << endl;
			Menu = 0; // returns to main menu (re-select)
		}

		else if (Menu == 7) { // 7. Print only Manager's boss'es title to console.
			cout << "Boss'es Title: " << obj.getBossTitle() << endl;
			cout << "------------------------------------------------" << endl;
			Menu = 0; // returns to main menu (re-select)
		}

		else if (Menu == 8) { // 8. exit
			cout << "End of program." << endl;
			break; //exits the while loop - terminate program
		}

		else { // invalid entree
			cout << "That is an invalid entree, please enter a number from  1 through 8." << endl;
			cout << "---------------------------------------------\n" << endl;
			Menu = 0; // returns to main menu (re-select)
		}
	}

	//Testing time below

	Manager M1;
	cout << M1.toString() << endl;
	Manager M2("F", "L", -200.0, "T");
	cout << M2.toString() << endl;
	Manager M3("Fran", "Lamar", 4000.99, "Vice President");
	cout << M3.toString() << endl;

	cout << M3.toString() << endl;
	M3.setLastName("P");
	cout << M3.toString() << endl;
	M3.setLastName("Prichard");
	cout << M3.toString() << endl;

	cout << M3.toString() << endl;
	M3.setFirstName("M");
	cout << M3.toString() << endl;
	M3.setFirstName("Lisa");
	cout << M3.toString() << endl;

	cout << "First Name: " << M3.getFirstName() << endl;
	cout << "Last Name: " << M3.getLastName() << endl;
	cout << "Full Name: " << M3.getFullName() << endl;
	M3.setSalary(-6000.55);
	M3.setBossTitle("X");
	cout << "Current Salary: $" << M3.getSalary() << endl;
	cout << "Current title of boss: " << M3.getBossTitle() << endl;
	M3.setBossTitle("Executive Manager");
	cout << "Current title of boss: " << M3.getBossTitle() << endl;


	system("pause");
	return 0;
}