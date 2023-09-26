#include "Controller.h"
#include <algorithm>
#include <exception>
#include <fstream>

void Controller::addDepartment(HospitalDepartment* departmentToAdd)
{
	this->allDepartments.push_back(departmentToAdd);
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
		if (currentDepartment->isEfficient() == true)
			efficientDepartments.push_back(currentDepartment);
	}
	return efficientDepartments;
}


bool sortByName(HospitalDepartment* hd1, HospitalDepartment* hd2)
{
	if (hd1->getName() < hd2->getName())
		return true;
	return false;
}

void Controller::writeToFile(std::string filename)
{
	std::ofstream outputFile{ filename };
	if (!outputFile.is_open())
		throw std::runtime_error{ "File is not opened!" };

	std::sort(this->allDepartments.begin(), this->allDepartments.end(), sortByName);
	for (const auto& currentDepartment : this->allDepartments)
	{
		outputFile << currentDepartment->toString();
	}
	outputFile.close();

}
