#pragma once
#include <string>

class Task
{
private:
	std::string description;
	int duration;
	int priority;
public:
	Task() : description(""), duration(0), priority(0) {};
	Task(std::string description, int duration, int priority) :
		description{ description },
		duration{ duration },
		priority{ priority } {};
	std::string getDescription() { return this->description; }
	int getDuration() { return this->duration; }
	int getPriority() { return this->priority; }
	friend std::istream& operator>>(std::istream& in, Task& taskToRead);
	std::string toString() const;
};

