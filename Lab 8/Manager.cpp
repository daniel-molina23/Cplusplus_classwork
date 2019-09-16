
#include"Manager.h"

Manager::Manager(const string & Fname, const string & Lname,
	double sal, const string & BTitle){


	if (Fname.length() >= MIN_NUM_CHARS_NAMES) { //>=3
		FirstName = Fname;
	}
	if (Lname.length() >= MIN_NUM_CHARS_NAMES) {//>=3
		LastName = Lname;
	}
	if (BTitle.length() >= MIN_NUM_CHARS_NAMES) {//>=3
		TitleOfBoss = BTitle;
	}

	salary = abs(sal); //positive salary

}

const string Manager::getBossTitle() const {
	return TitleOfBoss;
}

const string Manager::getFirstName()const {
	return FirstName;
}

const string Manager::getLastName() const {
	return LastName;
}

const string Manager::getFullName() const {
	return FirstName + " " + LastName;
}

double Manager::getSalary() const {
	return abs(salary); //returns positive entry
}

void Manager::setBossTitle(const string & Title) {
	if (Title.length() >= MIN_NUM_CHARS_NAMES) {//>=3
		TitleOfBoss = Title;
	}
	else {
		cout << "Title of Boss cannot be less than 3. The dafault value is used." << endl;
	}
}

void Manager::setFirstName(const string & Fname) {
	
	if (Fname.length() >= MIN_NUM_CHARS_NAMES) {//>=3
		FirstName = Fname;
	}
	else {
		cout << "The first name " << Fname << " does not have enough characters." << endl;
		cout << "We will set the first name to a default value of '" << FirstName << "'" << endl;
	}
}

void Manager::setLastName(const string & Lname) {
	if (Lname.length() >= MIN_NUM_CHARS_NAMES) {//>=3
		LastName = Lname;
	}
	else {
		cout << "The last name " << Lname << " does not have enough characters." << endl;
		cout << "We will set the last name to a default value of '" << LastName << "'" << endl;
	}
}

void Manager::setSalary(double sal) {
	salary = abs(sal);
}

const string Manager::toString() const {
	ostringstream bar;
	bar << "Manager's Data:" << endl;
	bar << "Name: " << getFullName() << endl;
	bar << "Boss'es Title: " << getBossTitle() << endl;
	bar << "Salary: $" << fixed << setprecision(3)
		<< getSalary() << endl;
	bar << "-----------------------------------------" << endl;
	return bar.str();
}
