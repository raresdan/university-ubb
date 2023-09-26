#pragma once
#include <string>
class Issue
{
private:
	std::string description;
	std::string status;
	std::string reporter;
	std::string solver;
public:
	Issue() : description(""), status(""), reporter(""), solver("") {}
	Issue(std::string description, std::string status, std::string reporter, std::string solver):
		description{description}, status{status}, reporter{reporter}, solver{solver} {}

	std::string getDescription() { return this->description; }
	std::string getStatus() { return this->status; }
	std::string getReporter() { return this->reporter; }
	std::string getSolver() { return this->solver; }

	void setSolver(std::string solver);
	void setStatus(std::string newStatus);

	friend std::istream& operator>>(std::istream& inputStream, Issue& issueToRead);
	std::string toString();
};

