#pragma once
#include <string>

class Patient
{
private:
	std::string name;
	std::string diagnosis;
	std::string specialisationNeeded;
	std::string doctor;
	std::string date;
public:
	Patient(): name(""), diagnosis("undiagnosed"), specialisationNeeded(""),doctor(""),date("") {}
	Patient(std::string name, std::string diagnosis, std::string specialisationNeeded, std::string doctor, std::string date) :
		name{name}, diagnosis{diagnosis}, specialisationNeeded{specialisationNeeded}, doctor{doctor}, date{date} {}

	std::string getName() { return this->name; }
	std::string getDiagnosis() { return this->diagnosis; }
	std::string getSpecialisation() { return this->specialisationNeeded; }
	std::string getDoctor() { return this->doctor; }
	std::string getDate() { return this->date; }
	
	friend std::istream& operator >> (std::istream& inputFile, Patient& patient);
	std::string toString();
};

