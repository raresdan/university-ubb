#include "TasksRepository.h"
#include "TaskNotOpen.h"
#include <fstream>

void TasksRepository::addTask(Task taskToAdd)
{
	this->allTasks.push_back(taskToAdd);
	this->writeTasks();
	this->notify();
}

void TasksRepository::deleteTask(int indexOfTaskToDelete)
{
	this->allTasks.erase(this->allTasks.begin() + indexOfTaskToDelete);
	this->writeTasks();
	this->notify();
}

void TasksRepository::startTask(int indexOfTaskToStart, int programmerId)
{
	Task currentTask = this->allTasks[indexOfTaskToStart];
	if (currentTask.getStatus() != "open")
		throw TaskNotOpen("Status is not open!");
	Task updatedTask{ currentTask.getDescription(), "in_progress", programmerId };
	this->allTasks[indexOfTaskToStart] = updatedTask;
	this->writeTasks();
	this->notify();
}

void TasksRepository::doneTask(int indexOfTaskDone, int programmerId)
{
	Task currentTask = this->allTasks[indexOfTaskDone];
	Task updatedTask{ currentTask.getDescription(), "closed", programmerId };
	this->allTasks[indexOfTaskDone] = updatedTask;
	this->writeTasks();
	this->notify();
}

void TasksRepository::readTasks()
{
	std::ifstream inputFile{ "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Training\\Final Exam\\TaskManager\\tasks.txt" };
	Task currentTask;
	while (inputFile >> currentTask)
	{
		this->allTasks.push_back(currentTask);
	}
	inputFile.close();
}


void TasksRepository::readProgrammers()
{
	std::ifstream inputFile{ "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Training\\Final Exam\\TaskManager\\programmers.txt" };
	Programmer currentProgrammer;
	while (inputFile >> currentProgrammer)
	{
		this->allProgrammers.push_back(currentProgrammer);
	}
	inputFile.close();
}

void TasksRepository::writeTasks()
{
	std::ofstream outputFile{ "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Training\\Final Exam\\TaskManager\\tasks.txt" };
	if (!outputFile.is_open())
	{
		throw std::runtime_error("File not opened!");
	}
	for (auto task : this->allTasks)
		outputFile << task.toString() << std::endl;
	
	outputFile.close();
}
