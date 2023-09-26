#include "Task.h"
#include <sstream>
#include <iostream>
#include <vector>

std::istream& operator>>(std::istream& in, Task& taskToRead)
{
    std::string line;
    std::getline(in, line);

    std::stringstream ss{ line };
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(ss, token, ';')) {
        tokens.push_back(token);
    }
    if (tokens.size() != 3)
        return in;

    taskToRead.description = tokens[0];
    taskToRead.duration = stoi(tokens[1]);
    taskToRead.priority = stoi(tokens[2]);
    return in;
}

std::string Task::toString() const
{
    std::stringstream result;
    result << "Description: " << this->description << ";"
        << "Duration: " << this->duration << ";"
        << "Priority: " << this->priority;
    return result.str();
}
