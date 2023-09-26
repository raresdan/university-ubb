#pragma once
#include <string>

class Programmer
{
	std::string name;
	int id;
public:
	Programmer() : name(""), id(NULL) {};
	Programmer(std::string name, int id): name{name}, id{id} {}

	std::string getName() { return this->name; }
	int getId() { return this->id; }

	friend std::istream& operator >> (std::istream& inputStream, Programmer& programmerToRead);

};

