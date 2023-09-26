#include "Programmer.h"
#include <sstream>
#include <vector>

std::istream& operator>>(std::istream& inputStream, Programmer& programmerToRead)
{
    std::string line, token;
    std::getline(inputStream, line);
    std::stringstream ss{ line };
    std::vector<std::string> tokens;
    while (std::getline(ss, token, ','))
    {
        tokens.push_back(token);
    }
    if (tokens.size() != 2)
        return inputStream;
    programmerToRead.name = tokens[0];
    programmerToRead.id = stoi(tokens[1]);
    return inputStream;
}
