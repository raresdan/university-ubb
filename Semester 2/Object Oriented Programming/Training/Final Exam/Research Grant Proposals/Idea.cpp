#include "Idea.h"
#include <sstream>
#include <vector>

std::istream& operator>>(std::istream& inputStream, Idea& idea)
{
    std::string line, token;
    std::getline(inputStream, line);
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    while (std::getline(ss, token, ',')) 
    {
        tokens.push_back(token);
    }
    if (tokens.size() != 5)
    {
		return inputStream;
	}
    idea.title = tokens[0];
    idea.description = tokens[1];
    idea.status = tokens[2];
    idea.creator = tokens[3];
    idea.duration = std::stoi(tokens[4]);
    return inputStream;
}

std::string Idea::toString()
{
    std::stringstream ss;
    ss << title << "," << description << "," << status << "," << creator << "," << duration;
    return ss.str();
}
