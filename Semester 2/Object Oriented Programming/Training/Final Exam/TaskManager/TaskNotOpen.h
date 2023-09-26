#pragma once
#include <exception>
#include <string>

class TaskNotOpen : public std::exception
{
private:
	std::string message;
public:
	TaskNotOpen(std::string throwMessage) : message{throwMessage} {}
	virtual const char* what() { return this->message.c_str(); }
};

