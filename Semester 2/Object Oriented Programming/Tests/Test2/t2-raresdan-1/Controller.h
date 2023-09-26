#pragma once
#include "HospitalDepartment.h"
#include "NeonatalUnit.h"
#include "Surgery.h"
#include <vector>

class Controller
{
private:
	std::vector<HospitalDepartment*> allDepartments;
public:
	Controller(std::vector<HospitalDepartment*> initialDepartments = {}) : allDepartments{ initialDepartments } 
	{
		Surgery* newSurgery = new Surgery{ "Recuperare", 45, 100 };
		Surgery* anotherNewSurgery = new Surgery{ "Spitalul-Militar", 70, 90 };
		NeonatalUnit* newNeonatal = new NeonatalUnit{ "Radu-Stanca", 50, 7 };
		this->addDepartment(newSurgery);
		this->addDepartment(newNeonatal);
		this->addDepartment(anotherNewSurgery);
	};
	void addDepartment(HospitalDepartment* hospitalDepartmentToAdd);
	std::vector<HospitalDepartment*> getAllDepartments();
	std::vector<HospitalDepartment*> getAllEfficientDepartments();
	void writeToFile(std::string filename);
};

