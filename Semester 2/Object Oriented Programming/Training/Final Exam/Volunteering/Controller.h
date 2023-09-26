#pragma once
#include <vector>
#include "Volunteer.h"
#include "Department.h"
#include "Subject.h"

class Controller : public Subject
{
private:
	std::vector<Volunteer> allVolunteers;
	std::vector<Department> allDepartments;

public:
	Controller() : allVolunteers(), allDepartments() {
		this->readDepartments();
		this->readVolunteers();
	}

	std::vector<Volunteer> getAllVolunteers() { return this->allVolunteers; }
	std::vector<Department> getAllDepartments() { return this->allDepartments; }

	void addVolunteer(Volunteer volunteerToAdd);
	void assignVolunteer(int index, std::string department);
	
	void readVolunteers();
	void readDepartments();

	void writeVolunteers();
};

