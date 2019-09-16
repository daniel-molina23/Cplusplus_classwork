#include<iostream>
#include<string>
#include <iomanip>
using namespace std;


void greeting();
//Greet user and explain software purpose

double getUserData(double & payRate, string & firstName, string & lastName, bool &healthPlan);
//input some eqution to calculate wage, etc. return hours worked

double getGrossSalary(double hoursWorked, double payRate);
//calculate ONLY

double getTaxWitheld(double GrossSalary);

double getNetSalary(double grossSalary, double taxWitheld, bool HealthPlan, string &
	HealthPlanStatusMessage);

void printResults(const string & firstName, const string & lastName, double hoursWorked,
	double payRate, double grossSalary, double taxWitheld, double netSalary,
	const string & HealthPlanStatus);

void goodbye();

const double TAXWITHHELD = 0.071;

int main()
{
	string firstName, lastName, healthPlanMessage;
	double payRate;
	bool healthPlan;


	cout << endl << endl;

	greeting();

	double hoursWorked = getUserData(payRate, firstName, lastName, healthPlan);

	cout << "--------------------------------------------------------";

	double grossSalary = getGrossSalary(hoursWorked, payRate);

	double taxWitheld = getTaxWitheld(grossSalary);

	double netSalary = getNetSalary(grossSalary, taxWitheld, healthPlan, healthPlanMessage);

	printResults(firstName, lastName, hoursWorked, payRate, grossSalary, taxWitheld, netSalary, healthPlanMessage);

	goodbye();

}


void greeting() {
	cout << "Welcome to the salary calculation program \n"
		<< "In this program we will ask for the information that would "
		<< "allow us to process your paycheck.\n"
		<< "We will collect information about hours worked, hourly pay "
		<< "rate and medical options.\n"
		<< "Processing will be completed in just a few minutes."
		<< "\n" << "\n" << endl;

	cout << "-------------------------------------------------------------------------\n"
		<< endl;
}

double getUserData(double & payRate, string & firstName, string & lastName, bool &healthPlan)
{
	int healthPlanInt;
	double hoursWorked;

	cout << "Please enter your first name [One word only]:" << endl;
	cin >> firstName;

	cout << "Please enter your last name [One word only]:" << endl;
	cin >> lastName;

	cout << "Please enter hours worked (positive number only):" << endl;
	cin >> hoursWorked;

	cout << "Please enter your hourly pay rate. [For example, enter 15.23 if your \n"
		<< "hourly pay rate is $15 and 23 cents]:" << endl;
	cin >> payRate;

	cout << "Enter 1 to purchase health plan or 0 (zero) to decline:";
	cin >> healthPlanInt;

	healthPlan = false;
	if (healthPlanInt == 1) {
		healthPlan = true;
	}
	return hoursWorked;

}

double getGrossSalary(double hoursWorked, double payRate) {
	double salary;

	if (hoursWorked > 40) {
		salary = (hoursWorked - 40)*1.5*payRate + 40 * payRate;
	}
	else {
		salary = hoursWorked * payRate;
	}

	return salary;

}
double getTaxWitheld(double GrossSalary) {

	return GrossSalary * TAXWITHHELD;
}

double getNetSalary(double grossSalary, double taxWitheld, bool HealthPlan, string & HealthPlanStatusMessage) {

	double netSalary = grossSalary - taxWitheld;


	if (HealthPlan) {
		if (netSalary >= 200) {
			netSalary -= 200;
			HealthPlanStatusMessage = "Employee opted for health insurance and was successfully registered";
		}
		else {
			HealthPlanStatusMessage = "Employee opted for health insurance but was declined because of insufficient salary.";
		}

	}
	else {
		HealthPlanStatusMessage = "Employee did not opt to register in health plan";
	}
	return netSalary;
}


void printResults(const string & firstName, const string & lastName, double hoursWorked,
	double payRate, double grossSalary, double taxWitheld, double netSalary,
	const string & HealthPlanStatus) {



	cout << "Here are the Employee Payroll details." << endl;
	cout << "Name: " << firstName << " " << lastName << endl;
	cout << "Hours worked: " << fixed << setprecision(2) << hoursWorked << " hours" << endl;
	cout << "Hourly Pay Rate: " << fixed << setprecision(2) << payRate << endl;
	cout << "Gross Salary: $" << fixed << setprecision(2) << grossSalary << endl;
	cout << "Tax withheld: $" << fixed << setprecision(2) << taxWitheld << endl;
	cout << HealthPlanStatus << endl;
	cout << "Employee net salary: $" << fixed << setprecision(2) << netSalary << endl;
	cout << "------------------------------------------" << endl;


}

void goodbye() {
	cout << "Thank you for using our program. \nPlease have a pleasant day." << endl;
}