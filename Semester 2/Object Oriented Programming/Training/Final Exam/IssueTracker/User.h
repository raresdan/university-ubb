#pragma once
#include <string>
class User
{
private:
	std::string name;
	std::string type;
public:
	User(): name(""), type("") {}
	User(std::string name, std::string type): name{name}, type{type} {}

	std::string getName() { return this->name; }
	std::string getType() { return this->type; }

	friend std::istream& operator>>(std::istream& inputStream, User& userToRead);
};

