#include "IssuesRepository.h"
#include <fstream>
#include <sstream>

void IssuesRepository::addIssue(Issue issueToAdd)
{
	for (auto currentIssue : this->allIssues)
	{
		if (issueToAdd.getDescription() == currentIssue.getDescription() || issueToAdd.getDescription() == "")
			throw std::exception("Issue exists or field incomplete!");
	}
	this->allIssues.push_back(issueToAdd);
	this->notify();
	this->writeIssues();
}

void IssuesRepository::removeIssue(int indexOfIssueToRemove)
{
	if (indexOfIssueToRemove < 0 || indexOfIssueToRemove >= this->allIssues.size())
		throw std::exception("Tutorial doesn't exists!");
	this->allIssues.erase(this->allIssues.begin() + indexOfIssueToRemove);
	this->notify();
	this->writeIssues();
}

void IssuesRepository::resolveIssue(int indexOfIssueToResolve, std::string resolver)
{

	if (indexOfIssueToResolve < 0 || indexOfIssueToResolve >= this->allIssues.size())
		throw std::exception("Tutorial doesn't exists!");
	Issue updatedIssue{ this->allIssues[indexOfIssueToResolve].getDescription(),"closed", this->allIssues[indexOfIssueToResolve].getReporter(), resolver };
	this->allIssues[indexOfIssueToResolve] = updatedIssue;
	this->notify();
	this->writeIssues();
}

void IssuesRepository::readUsers()
{
	std::ifstream inputFile("D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Training\\Final Exam\\IssueTracker\\users.txt");
	User currentUser;
	while (inputFile >> currentUser)
	{
		this->allUsers.push_back(currentUser);
	}
	inputFile.close();
}

void IssuesRepository::readIssues()
{
	std::ifstream inputFile("D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Training\\Final Exam\\IssueTracker\\issues.txt");
	Issue currentIssue;
	while (inputFile >> currentIssue)
	{
		this->allIssues.push_back(currentIssue);
	}
	inputFile.close();
}

void IssuesRepository::writeIssues()
{
	std::ofstream outputFile{ "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Training\\Final Exam\\IssueTracker\\issues.txt" };
	if (!outputFile.is_open())
		throw std::runtime_error("File not opened!");
	std::stringstream stringStream;
	for (auto currentIssue : this->allIssues)
	{
		std::stringstream stringStream;
		stringStream << currentIssue.getDescription() << ","
			<< currentIssue.getStatus() << ","
			<< currentIssue.getReporter() << ","
			<< currentIssue.getSolver() << std::endl;
		outputFile << stringStream.str();
	}
	outputFile.close();
}
