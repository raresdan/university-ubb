#include "Controller.h"
#include<fstream>

void Controller::readDoctors()
{
	std::ifstream inputFile{ "doctors.txt" };
	Doctor currentDoctor;
	while (inputFile >> currentDoctor)
	{
		this->allDoctors.push_back(currentDoctor);
	}
	inputFile.close();
}

void Controller::readPatients()
{
	std::ifstream inputFile{ "patients.txt" };
	Patient currentPatient;
	while (inputFile >> currentPatient)
	{
		this->allPatients.push_back(currentPatient);
	}
	inputFile.close();
}

void Controller::writePatients()
{
	std::ofstream outputFile{ "patients.txt" };
	for (auto patient : allPatients)
	{
		outputFile << patient.toString() << std::endl;
	}

	outputFile.close();
}

void Controller::addPatient(Patient patientToAdd)
{
	if (patientToAdd.getName() == "")
		throw std::exception("Invalid data!");
	this->allPatients.push_back(patientToAdd);
	this->writePatients();
	this->notify();
}

void Controller::updatePatient(Patient patientToUpdate, std::string newDiagnosis, std::string newSpecialisation, std::string newDoctor)
{
	if (newDiagnosis == "undiagnosed" || newDiagnosis == "")
		throw std::exception("New diagnosis must be valid! ");
	if(newSpecialisation == "-")
		throw std::exception("Specialisation cannot be empty! ");
	int index = 0;
	for (auto patient : allPatients)
	{
		if (patientToUpdate.getName() == patient.getName())
			break;
		index++;
	}
	Patient updatedPatient{ patientToUpdate.getName(), newDiagnosis, newSpecialisation, newDoctor , patientToUpdate.getDate()};
	this->allPatients[index] = updatedPatient;
	this->writePatients();
	this->notify();
}
