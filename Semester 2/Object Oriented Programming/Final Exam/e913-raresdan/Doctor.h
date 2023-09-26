#pragma once
#include <string>

class Doctor
{
private:
	std::string name;
	std::string specialisation;

public:
	Doctor(): name(""), specialisation("") {}
	Doctor(std::string name, std::string specialisation) : name{name}, specialisation{specialisation} {}

	std::string getName() { return this->name; }
	std::string getSpecialisation() { return this->specialisation; }

	friend std::istream& operator >> (std::istream& inputFile, Doctor& doctor);

};

