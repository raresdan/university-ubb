#include "Task.h"
#include <sstream>
#include <vector>

std::istream& operator>>(std::istream& inputStream, Task& taskToRead)
{
    std::string line, token;
    std::getline(inputStream, line);
    std::stringstream ss{ line };
    std::vector<std::string> tokens;
    while (std::getline(ss, token, ','))
    {
        tokens.push_back(token);
    }
    if (tokens.size() != 3)
        return inputStream;
    taskToRead.description = tokens[0];
    taskToRead.status = tokens[1];
    taskToRead.programmerId = stoi(tokens[2]);
    return inputStream;
}

std::string Task::toString()
{
    std::stringstream ss;
    ss << this->description << "," << this->status << "," << this->programmerId;
    return ss.str();
}
