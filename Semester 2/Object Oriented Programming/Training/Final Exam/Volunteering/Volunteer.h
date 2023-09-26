#pragma once
#include <string>
#include <vector>

class Volunteer
{
private:
	std::string name;
	std::string email;
	std::vector<std::string> listOfInterests;
	std::string department;
public:
	Volunteer(): name(""), email(""), listOfInterests(), department("") {}
	Volunteer(std::string name, std::string email, std::vector<std::string> listOfInterests, std::string department)
		: name(name), email(email), listOfInterests(listOfInterests), department(department) {}

	std::string getName() { return this->name; }
	std::string getEmail() { return this->email; }
	std::string getDepartment() { return this->department; }
	std::vector<std::string> getListOfInterest() { return this->listOfInterests; }

	friend std::istream& operator >> (std::istream& inputFile, Volunteer& volunteerToRead);
	std::string toString();
};

