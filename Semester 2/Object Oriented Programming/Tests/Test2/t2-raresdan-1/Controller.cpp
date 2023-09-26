#include "Controller.h"
#include <fstream>
#include <exception>
#include <algorithm>

bool sortByName(HospitalDepartment* firstDepartment, HospitalDepartment* secondDepartment)
{
	return firstDepartment->getHospitalName() < secondDepartment->getHospitalName();
}

void Controller::addDepartment(HospitalDepartment* hospitalDepartmentToAdd)
{
	this->allDepartments.push_back(hospitalDepartmentToAdd);
}

std::vector<HospitalDepartment*> Controller::getAllDepartments()
{
	return this->allDepartments;
}

std::vector<HospitalDepartment*> Controller::getAllEfficientDepartments()
{
	std::vector<HospitalDepartment*> efficientDepartments;
	for (auto currentDepartment : this->allDepartments)
	{
		if (currentDepartment->isEfficient())
			efficientDepartments.push_back(currentDepartment);
	}
	return efficientDepartments;
}

void Controller::writeToFile(std::string filename)
{
	std::ofstream outputFile{ filename };
	if (!outputFile.is_open())
		throw std::runtime_error("File not opened!");
	std::sort(this->allDepartments.begin(), this->allDepartments.end(), sortByName);
	for (auto currentDepartment : this->allDepartments)
	{
		outputFile << currentDepartment->toString();
	}
	outputFile.close();

}
