#pragma once
#include <string>
class Task
{
private:
	std::string description;
	std::string status;
	int programmerId;
public:
	Task(): description(""), status(""), programmerId(NULL) {}
	Task(std::string description, std::string status, int id) : description{description}, status{status}, programmerId{id} {}

	std::string getDescription() { return this->description; }
	std::string getStatus() { return this->status; }
	int getId() { return this->programmerId; }

	friend std::istream& operator >> (std::istream& inputStream, Task& taskToRead);
	std::string toString();
 };

