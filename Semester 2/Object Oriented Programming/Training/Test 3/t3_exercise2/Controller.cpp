#include "Controller.h"
#include <fstream>

std::vector<Item> Controller::getAllItems()
{
	return this->allItems;
}

void Controller::deleteItem(std::string category, std::string name)
{
	int index = 0;
	for (auto currentItem : this->allItems)
	{
		if (currentItem.getCategory() == category && currentItem.getName() == name)
			break;
		index++;
	}
	this->allItems.erase(this->allItems.begin() + index);
}

void Controller::filterItems(std::string category)
{
	std::vector<Item> filteredItems = {};
	for (auto currentItem : this->allItems)
	{
		if (currentItem.getCategory() == category)
			filteredItems.push_back(currentItem);
	}
	this->allItems = filteredItems;
}

void Controller::readFromFile()
{
	std::ifstream inputFile(this->filename);
	Item currentItem;
	while (inputFile >> currentItem)
	{
		this->allItems.push_back(currentItem);
	}
	inputFile.close();
}
