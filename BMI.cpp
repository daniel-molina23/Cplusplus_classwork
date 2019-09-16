// Function Definitions

//can read the entire thing from the BMI.h file
#include "BMI.h"

BMI::BMI() {
	//we can see the member variables, initialize the private sector
	newHeight = 0;
	newWeight = 0.0;
}

//overloading constructor
BMI::BMI(string name, int height, double weight) {
	newName = name;
	newHeight = height;
	newWeight = weight;

} //set member variables to what ever we passed in

BMI::~BMI(){

}

string BMI::getName() const {
	return newName;
}

int BMI::getHeight() const {
	return newHeight;
}

double BMI::getWeight() const {
	return newWeight;
}

void BMI::setName(string name) {
	newName = name;
}//passed in name as a parameter

void BMI::setHeight(int height) {
	newHeight = height;
}

void BMI::setWeight(double weight) {
	newWeight = weight;
}

double BMI::calculateBMI() {
	return ((newWeight * 703) / (newHeight*newHeight));
}
