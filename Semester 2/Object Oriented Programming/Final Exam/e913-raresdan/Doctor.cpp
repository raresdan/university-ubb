#include "Doctor.h"
#include <sstream>
#include <vector>

std::istream& operator>>(std::istream& inputFile, Doctor& doctor)
{
	std::string line, token;
	std::getline(inputFile, line);
	std::stringstream ss{ line };
	std::vector<std::string> tokens;
	while (std::getline(ss, token, ','))
	{
		tokens.push_back(token);
	}
	if (tokens.size() != 2)
		return inputFile;
	doctor.name = tokens[0];
	doctor.specialisation = tokens[1];
	return inputFile;
}
