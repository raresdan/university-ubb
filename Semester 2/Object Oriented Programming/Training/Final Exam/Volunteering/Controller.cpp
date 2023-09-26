#include "Controller.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void Controller::addVolunteer(Volunteer volunteerToAdd)
{
	if (volunteerToAdd.getName() == "" || volunteerToAdd.getEmail() == "")
		throw std::exception("Name or E-Mail are empty!");
	this->allVolunteers.push_back(volunteerToAdd);
	this->writeVolunteers();
	this->notify();
}

void Controller::assignVolunteer(int index, std::string department)
{
	std::vector<Volunteer> unassignedVolunteers;
	for (auto volunteer : allVolunteers)
	{
		if (volunteer.getDepartment() == "-")
			unassignedVolunteers.push_back(volunteer);
	}
	Volunteer oldVolunteer = unassignedVolunteers[index];
	index = 0;
	for (auto volunteer : allVolunteers)
	{
		if (volunteer.getName() == oldVolunteer.getName() && volunteer.getEmail() == oldVolunteer.getEmail())
			break;
		index++;
	}
	Volunteer updatedVolunteer{ oldVolunteer.getName(), oldVolunteer.getEmail(),oldVolunteer.getListOfInterest(), department };
	this->allVolunteers[index] = updatedVolunteer;
	this->writeVolunteers();
	this->notify();
}

void Controller::readVolunteers()
{
	std::ifstream inputFile{ "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Training\\Final Exam\\Volunteering\\volunteers.txt" };
	Volunteer currentVolunteer;
	while (inputFile >> currentVolunteer)
	{
		this->allVolunteers.push_back(currentVolunteer);
	}
	inputFile.close();
}


void Controller::readDepartments()
{
	std::ifstream inputFile{ "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Training\\Final Exam\\Volunteering\\departments.txt" };
	Department currentDepartment;
	while (inputFile >> currentDepartment)
	{
		this->allDepartments.push_back(currentDepartment);
	}
	inputFile.close();
}

void Controller::writeVolunteers()
{
	std::ofstream outputFile{ "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Training\\Final Exam\\Volunteering\\volunteers.txt" };
	if (!outputFile.is_open())
		throw std::exception("File not opened!");
	for(auto currentVolunteer:this->allVolunteers)
	{
		outputFile << currentVolunteer.toString() << std::endl;
	}

}
