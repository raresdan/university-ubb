#include "Item.h"
#include <vector>
#include <fstream>
#include <sstream>

std::istream& operator>>(std::istream& inputStream, Item& itemToRead)
{
	std::string line;
	std::getline(inputStream, line);
	std::stringstream ss{ line };
	std::string token;
	std::vector< std::string> tokens = {};
	while (std::getline(ss, token, ';'))
	{
		tokens.push_back(token);
	}
	if (tokens.size() != 3)
		return inputStream;
	itemToRead.category = tokens[0];
	itemToRead.name = tokens[1];
	itemToRead.quantity = stoi(tokens[2]);
	return inputStream;
}

std::string Item::toString()
{
	std::stringstream stringStream;
	stringStream << "Category: " << this->category << ";"
		<< "Name: " << this->name << ";"
		<< "Quantity: " << this->quantity;
	return stringStream.str();
}
