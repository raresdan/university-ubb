#include "Researcher.h"
#include <sstream>
#include <vector>

std::istream& operator>>(std::istream& inputStream, Researcher& researcher)
{
    std::string line, token;
    std::getline(inputStream, line);
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    while (std::getline(ss, token, ',')) {
		tokens.push_back(token);
	}
    if (tokens.size() != 2) {
		return inputStream;
	}
    researcher.name = tokens[0];
	researcher.position = tokens[1];
	return inputStream;
}
