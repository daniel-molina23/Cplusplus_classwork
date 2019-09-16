/*
Name:Daniel Molina
Class: CS52
Lab #: Test 1
Compiler Used: Visual Studio
Operating System Used: Windows 10
Date and Time of Last successful Compilation: March 30, 2019 5:30pm
Date and Time of when program verified all test results: March 30, 2019 6:00pm
*/


#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

size_t FillArrays(string Names[], int HoursWorked[], double PayRates[]);
//inputs user entered data into all three arrays

double getSalary(int HoursWorked, double PayRates);
//function that computes the salary of each employee 
//and total company salary given to all employees


int main()
{
	string Names[1000];
	int HoursWorked[1000];
	double PayRates[1000];
	
	int size = FillArrays(Names, HoursWorked, PayRates);
	//calls function to input data into all three arrays

	double sum = 0; 
	int count = 0; 

	cout << "\nWelcome!" << endl;

	for (int n = 0; n < size; n++) {
	
		cout << "Hello " << Names[n] << endl;

		cout << "You worked " << HoursWorked[n]
			<< " hours in the week." << endl;

		double salary = getSalary(HoursWorked[n], PayRates[n]);

		cout << "Your hourly pay rate: $"
			<< PayRates[n] << endl;

		cout << "Your weekly salary: $"
			<< setprecision(2) << fixed << salary << endl;

		cout << "---------------------------------"
			<< endl;

		sum += salary;  //obtain total salaries

		count = n+1;    //count number of people
	}

	cout << "Number of employees entered " << count << " :" << endl;
	cout << "Total company pay roll: $" << sum << endl;
	cout << "Good bye." << endl;


	system("pause");
	
	return 0;
}



double getSalary(int HoursWorked, double PayRate) {
	
	double salary = 0;

	const double fullTimeHours = 40;
	
	if (HoursWorked <= 40) {   //normal pay rate

		salary = HoursWorked * PayRate;

	}else {                   //overtime pay rate
	
		double overtimePay = ((double)HoursWorked - fullTimeHours)*1.50*PayRate;

		salary = (fullTimeHours * PayRate) + overtimePay;       
		//total pay with overtime if going over 40 hours/week

	}

	return salary;
}




size_t FillArrays(string Names[], int HoursWorked[], double PayRates[]) {

	int i = 0;

	while (cin) {
		
		string firstName = "";
		
		string lastName = "";
				
		
		cout << "Enter employee's first name or EOF character to exit:" << endl;
		cin>>firstName;


		if (!cin) {
			break;
		}        //exits inputs upon inputting control + (Z or D)


		cout << "Enter employee's last name:" << endl;
		cin >> lastName;

		string fullName = firstName + " " + lastName;
		
		Names[i] = fullName;

		cout << "Enter hours in the week, worked by employee [whole number only]:" << endl;
		cin >> HoursWorked[i];
		
		cout << "Enter employee's hourly pay rate(xx.yy):" << endl;
		cin >> PayRates[i];
		
		i++; //multiple iterations

	} //end of loop

	return i;
}
