#include "Patient.h"
#include <sstream>
#include <vector>

std::istream& operator>>(std::istream& inputFile, Patient& patient)
{
	std::string line, token;
	std::getline(inputFile, line);
	std::stringstream ss{ line };
	std::vector<std::string> tokens;
	while (std::getline(ss, token, ','))
	{
		tokens.push_back(token);
	}
	if (tokens.size() != 5)
		return inputFile;
	patient.name = tokens[0];
	patient.diagnosis = tokens[1];
	patient.specialisationNeeded = tokens[2];
	patient.doctor = tokens[3];
	patient.date = tokens[4];
	return inputFile;
}

std::string Patient::toString()
{
	std::stringstream ss;
	ss << this->name << "," << this->diagnosis << "," << this->specialisationNeeded << "," << this->doctor << "," << this->date;
	return ss.str();
}
