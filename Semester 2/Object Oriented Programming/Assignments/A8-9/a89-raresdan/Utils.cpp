#include "Utils.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

std::string trim(const std::string& stringToTrim)
{
	std::string result(stringToTrim);
	size_t position = result.find_first_not_of(" ");
	if (position != -1)
		result.erase(0, position);
	position = result.find_last_not_of(" ");
	if (position != std::string::npos)
		result.erase(position + 1);
	return result;
}

vector<string> tokenize(const string& stringToTokenize, char delimiter)
{
	vector <string> result;
	stringstream ss(stringToTokenize);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);
	return result;
}