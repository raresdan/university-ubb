#pragma once
#include "Task.h"
#include <vector>
#include <fstream>
#include <iostream>

class Controller
{
private:
	std::vector<Task> allTasks;
	std::string filename;
public:
	Controller(std::string filename, std::vector<Task> initialTasks = {}) : filename{filename}, allTasks{initialTasks}
	{
		this->readFromFile();
	}
	std::vector<Task> getAllTasks();
	int showDuration(int priority);
	void readFromFile();
};