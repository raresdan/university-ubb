#pragma once
#include <string>

class Researcher
{
private:
	std::string name;
	std::string position;
public:
	Researcher(): name(""), position("") {}
	Researcher(std::string name, std::string position) : name(name), position(position) {}

	std::string getName() { return name; }
	std::string getPosition() { return position; }

	friend std::istream& operator>>(std::istream& inputStream, Researcher& researcher);
};

