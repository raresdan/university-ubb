#include "Tests.h"
#include "TasksRepository.h"
#include <assert.h>

void Tests::testRemove()
{
	TasksRepository fakeRepository;
	Task taskToRemove = fakeRepository.getAllTasks()[0];
	int size = fakeRepository.getAllTasks().size();
	fakeRepository.deleteTask(0);
	assert(fakeRepository.getAllTasks().size() == size - 1);
	fakeRepository.addTask(taskToRemove);
}

void Tests::testUpdate()
{
	TasksRepository fakeRepository;
	Task taskToRevertChanges = fakeRepository.getAllTasks()[0];
	assert(fakeRepository.getAllTasks()[0].getStatus() == "open");
	fakeRepository.startTask(0, 1);
	assert(fakeRepository.getAllTasks()[0].getStatus() == "in_progress");
	assert(fakeRepository.getAllTasks()[0].getId() == 1);
	fakeRepository.doneTask(0, 1);
	assert(fakeRepository.getAllTasks()[0].getStatus() == "closed");
	assert(fakeRepository.getAllTasks()[0].getId() == 1);
	fakeRepository.deleteTask(0);
	fakeRepository.addTask(taskToRevertChanges);
}

void Tests::testAll()
{
	this->testRemove();
	this->testUpdate();
}
