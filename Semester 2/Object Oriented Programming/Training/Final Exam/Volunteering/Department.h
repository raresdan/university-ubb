#pragma once
#include <string>
#include <vector>
#include "Volunteer.h"

class Department
{
private:
	std::string name;
	std::string description;
public:
	Department() : name(""), description(""){}
	Department(std::string name, std::string description) : name{name}, description{description} {}
	std::string getName() { return this->name; }
	std::string getDescription() { return this->description; }

	friend std::istream& operator >> (std::istream& inputFile, Department& departmentToRead);
	std::string toString(Department department);
};

