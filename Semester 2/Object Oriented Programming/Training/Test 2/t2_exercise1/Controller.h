#pragma once
#include "HospitalDepartment.h"
#include "Surgery.h"
#include "NeonatalUnit.h"
#include <vector>

class Controller
{
private:
	std::vector<HospitalDepartment*> allDepartments;
public:
	Controller(std::vector<HospitalDepartment*> initialDepartments = {}) 
	{
		Surgery* s = new Surgery{"Recuperare", 10, 15};
		Surgery* s1 = new Surgery{ "Recuperare", 45, 15 };
		NeonatalUnit* nu = new NeonatalUnit{ "Radu Stanca", 20, 15, 16, 21};
		this->addDepartment(s);
		this->addDepartment(s1);
		this->addDepartment(nu);
	};
	void addDepartment(HospitalDepartment* departmentToAdd);
	std::vector<HospitalDepartment*> getAllDepartments();
	std::vector<HospitalDepartment*> getAllEfficientDepartments();
	void writeToFile(std::string filename);
};

