#include "User.h"
#include <fstream>
#include <sstream>
#include <vector>

std::istream& operator>>(std::istream& inputStream, User& userToRead)
{
	std::string line;
	std::getline(inputStream, line);
	std::stringstream ss{ line };
	std::string token;
	std::vector<std::string> tokens = {};
	while (std::getline(ss, token, ','))
	{
		tokens.push_back(token);
	}
	if (tokens.size() != 2)
		return inputStream;
	userToRead.name = tokens[0];
	userToRead.type = tokens[1];
	return inputStream;
}
