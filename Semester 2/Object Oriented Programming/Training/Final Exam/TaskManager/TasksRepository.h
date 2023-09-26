#pragma once
#include "Task.h"
#include "Programmer.h"
#include "Subject.h"
#include <vector>
#include <algorithm>

class TasksRepository : public Subject
{
private:
	std::vector<Task> allTasks;
	std::vector<Programmer> allProgrammers;
public:
	TasksRepository(): allTasks(), allProgrammers() 
	{
		this->readTasks();
		this->readProgrammers();
		std::sort(this->allTasks.begin(), this->allTasks.end(), [](Task task1, Task task2) {return task1.getStatus() > task2.getStatus(); });
	}

	std::vector<Task> getAllTasks() { return this->allTasks; }
	std::vector<Programmer> getAllProgrammers() { return this->allProgrammers; }

	void addTask(Task taskToAdd);
	void deleteTask(int indexOfTaskToDelete);
	void startTask(int indexOfTaskToStart, int programmerId);
	void doneTask(int indexOfTaskDone, int programmerId);

	void readTasks();
	void readProgrammers();

	void writeTasks();
};

