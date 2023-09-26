#include "Issue.h"
#include <vector>
#include <sstream>

std::istream& operator>>(std::istream& inputStream, Issue& issueToRead)
{
	std::string line;
	std::getline(inputStream, line);
	std::stringstream ss{ line };
	std::string token;
	std::vector<std::string> tokens = {};
	while (std::getline(ss, token, ','))
	{
		tokens.push_back(token);
	}
	if (tokens.size() != 4)
		return inputStream;
	issueToRead.description = tokens[0];
	issueToRead.status = tokens[1];
	issueToRead.reporter = tokens[2];
	issueToRead.solver = tokens[3];
	return inputStream;
}

void Issue::setSolver(std::string solver)
{
	this->solver = solver;
}

void Issue::setStatus(std::string newStatus)
{
	this->status = newStatus;
}

std::string Issue::toString()
{
	std::stringstream stringStream;
	stringStream << "Description: " << this->description << ","
		<< "Status: " << this->status << ","
		<< "Reporter: " << this->reporter << ","
		<< "Solver: " << this->solver;
	return stringStream.str();
}
