#pragma once
#include "Doctor.h"
#include "Patient.h"
#include "Subject.h"
#include <vector>
#include <algorithm>

class Controller : public Subject
{
private:
	std::vector<Doctor> allDoctors;
	std::vector<Patient> allPatients;
public:
	Controller() : allDoctors(), allPatients() 
	{
		this->readDoctors();
		this->readPatients();

		std::sort(allPatients.begin(), allPatients.end(), [](Patient p1, Patient p2) 
			{
				//std::string p1Date = p1.getDate();
				//std::string p2Date = p2.getDate();
				//
				//int day1= stoi(p1Date.substr(0, 2));
				//int day2 = stoi(p2Date.substr(0, 2));
				//
				//int month1 = stoi(p1Date.substr(3, 5));
				//int month2 = stoi(p2Date.substr(3, 5));
				//
				//int year1 = stoi(p2Date.substr(6, 10));
				//int year2 = stoi(p2Date.substr(6, 10));

				//if (year1 >= year2)
				//	return true;
				return p1.getDate() < p2.getDate(); 
			});
	}

	std::vector<Doctor> getAllDoctors() { return this->allDoctors; }
	std::vector<Patient> getAllPatients() { return this->allPatients; }

	void readDoctors();
	void readPatients();

	void writePatients();

	void addPatient(Patient patientToAdd);
	void updatePatient(Patient patientToUpdate, std::string newDiagnosis, std::string newSpecialisation, std::string newDoctor);
};

