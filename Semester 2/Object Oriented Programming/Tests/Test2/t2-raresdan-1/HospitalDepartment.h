#pragma once
#include <string>

class HospitalDepartment
{
protected:
	std::string hospitalName;
	int numberOfDoctors;
public:
	HospitalDepartment(std::string hospitalName, int numberOfDoctors) :
		hospitalName{ hospitalName },
		numberOfDoctors{ numberOfDoctors } {};
	virtual bool isEfficient() = 0;
	virtual std::string toString() = 0;
	std::string getHospitalName()
	{
		return this->hospitalName;
	}
};

