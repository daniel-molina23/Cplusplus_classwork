#include "CertDeposit.h"

CertDeposit::CertDeposit() {
	//initializing variables
	Principal = 0.0;
	AccountNumber = 0;
	FirstName = "";
	LastName = "";
	InterestRate = 0.0;
	DepositYears = 0;
	NumCompounding = 0;
}

CertDeposit::CertDeposit(double In_Principal, int In_AccountNumber, 
						string In_FirstName, string In_LastName, 
						double In_InterestRate, double In_DepositYears,
						int In_NumCompounding)
{

	Principal = In_Principal;
	AccountNumber = In_AccountNumber;
	FirstName = In_FirstName;
	LastName = In_LastName;
	InterestRate = In_InterestRate;
	DepositYears = In_DepositYears;
	NumCompounding = In_NumCompounding;
}

CertDeposit::~CertDeposit() {

}

double CertDeposit::getPrincipal() const {
	return abs(Principal);
}

const string CertDeposit::getFirstName() const {
	return FirstName;
}

const string CertDeposit::getLastName() const {
	return LastName;
}

const string CertDeposit::getFullName() const {
	return (FirstName + " " + LastName);
}


int CertDeposit::getAccountNumber() const {
	return AccountNumber;
}


double CertDeposit::getDepositYears() const {
	return abs(DepositYears);
}


int CertDeposit::getNumCompounding() const {
	return abs(NumCompounding);
}

double CertDeposit::getAnnualInterestRate() const {
	return abs(InterestRate*100);
}

double CertDeposit::getAccumulation() const {
	return (Principal * pow((1 + (InterestRate / NumCompounding)), (DepositYears*NumCompounding)));
	
} //used the accumulation formula


double CertDeposit::getInterestAccrued() const {
	return ((Principal * pow((1 + (InterestRate / NumCompounding)), (DepositYears*NumCompounding))) - Principal);
} //sum of total interest minus principal


const string CertDeposit::toString(vector<CertDeposit> CDVec) const {

	
	ostringstream bar;	

	unsigned int size = CDVec.size();

	for (unsigned int i = 0; i < size; i++) {
	
		bar << "Account Number: "
			<< CDVec[i].getAccountNumber();
	
		bar << endl << "Name: "
			<< CDVec[i].getFullName();
	
		bar << endl << "Original Deposit: $"
			<< fixed << setprecision(2) << CDVec[i].getPrincipal();
	
		bar << endl << "Annual Interest Rate: "
			<< fixed << setprecision(2) << CDVec[i].getAnnualInterestRate(); ////IS THIS EQUATION REALLY RIGHT THO????????
	
		bar << endl << "Number of years of deposit: "
			<< fixed << setprecision(2) << CDVec[i].getDepositYears();
	
		bar << endl << "Number of times compounded per year: "
			<< CDVec[i].getNumCompounding();
	
		bar << endl << "Total accumulation: $"
			<< fixed << setprecision(2) << CDVec[i].getAccumulation();
	
		bar << endl << "Interest accrued: $"
			<< fixed << setprecision(2) << CDVec[i].getInterestAccrued();
	
		bar << endl << "--------------------------------" << endl;
	} //end of 'for' loop

		cout << bar.str();
		return bar.str();
} //outputing all values for user when selecting (Menu == '2')


void CertDeposit::setLastName(string In_LastName){
	LastName = In_LastName;
}
