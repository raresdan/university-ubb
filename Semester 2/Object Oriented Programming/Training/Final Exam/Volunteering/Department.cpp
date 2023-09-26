#include "Department.h"
#include <istream>
#include <sstream>
#include <vector>

std::istream& operator>>(std::istream& inputFile, Department& departmentToRead)
{
    std::string line, token;
    std::getline(inputFile, line);
    std::stringstream ss{ line };
    std::vector<std::string> tokens;
    while (std::getline(ss, token, ','))
    {
        tokens.push_back(token);
    }
    if (tokens.size() != 2)
        return inputFile;
    departmentToRead.name = tokens[0];
    departmentToRead.description = tokens[1];
    return inputFile;
}

std::string Department::toString(Department department)
{
    std::stringstream ss;
    ss << "Name: " << department.name << "," << "Description: " << department.description << std::endl;
    return ss.str();
}
