#include "Volunteer.h"
#include <sstream>

std::istream& operator>>(std::istream& inputFile, Volunteer& volunteerToRead)
{
    std::string line, token;
    std::getline(inputFile, line);
    std::stringstream ss{ line };
    std::vector<std::string> tokens;
    while (getline(ss, token, ','))
    {
        tokens.push_back(token);
    }
    if (tokens.size() != 4)
        return inputFile;
    volunteerToRead.name = tokens[0];
    volunteerToRead.email = tokens[1];
    std::string interest;
    std::istringstream stream{ tokens[2]};
    volunteerToRead.listOfInterests.clear();
    while (getline(stream, interest, ';'))
    {
        volunteerToRead.listOfInterests.push_back(interest);
    }
    volunteerToRead.department = tokens[3];
    return inputFile;
}

std::string Volunteer::toString()
{
    std::stringstream ss;
    ss << this->getName() << ","
        << this->getEmail() << ",";
    for (auto interest : this->getListOfInterest())
    {
        if (interest == this->getListOfInterest()[this->getListOfInterest().size()-1])
        {
            ss << interest;
        }
        else
            ss << interest << ";";
    }
    ss << ","
        << this->getDepartment();
    return ss.str();
}
