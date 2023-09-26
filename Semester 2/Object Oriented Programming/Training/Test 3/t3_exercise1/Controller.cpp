#include "Controller.h"
#include <algorithm>

bool sortByPriority(Task task1, Task task2)
{
    return task1.getPriority() < task2.getPriority();
}

std::vector<Task> Controller::getAllTasks()
{
    std::sort(this->allTasks.begin(), this->allTasks.end(), sortByPriority);
    return this->allTasks;
}

int Controller::showDuration(int priority)
{
    int totalDuration = 0;
    for (auto currentTask : this->allTasks)
    {
        if (currentTask.getPriority() == priority)
            totalDuration += currentTask.getDuration();
    }
    return totalDuration;
}

void Controller::readFromFile()
{
    std::ifstream inputFile(this->filename);
    if (!inputFile.is_open())
        std::cout << "The file could not be opened!";
    Task currentTask;
    while (inputFile >> currentTask) {
        this->allTasks.push_back(currentTask);
    }
    inputFile.close();
}
