#pragma once
#include <string>
#include <sstream>

class HospitalDepartment
{
protected:
	std::string hospitalName;
	int numberOfDoctors;
public:
	HospitalDepartment(std::string name, int doctors) : hospitalName{ name }, numberOfDoctors{ doctors } {};
	virtual bool isEfficient() = 0;
	virtual std::string toString() = 0;
	std::string getName() {
		return this->hospitalName;
	}

};

