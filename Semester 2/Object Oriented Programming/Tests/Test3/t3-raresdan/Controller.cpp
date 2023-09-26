#include "Controller.h"
#include <fstream>
#include <algorithm>

bool sortByCategoryAndName(Item firstItem, Item secondItem)
{
	if (firstItem.getCategory() <= secondItem.getCategory() && firstItem.getName() <= secondItem.getName())
	{
		if (firstItem.getName() <= secondItem.getName())
			return true;
	}
	return false;
}

std::vector<Item> Controller::getAllItems()
{
	std::sort(this->allItems.begin(), this->allItems.end(), sortByCategoryAndName);
	return this->allItems;
}

std::vector<Item> Controller::searchItem(std::string searchedString)
{
	std::vector<Item> searchedItems = {};
	for (auto currentItem : this->allItems)
	{
		if (currentItem.getCategory() == searchedString || currentItem.getName() == searchedString)
			searchedItems.push_back(currentItem);
	}
	return searchedItems;
}

bool sortByQuantity(Item firstItem, Item secondItem)
{
	return firstItem.getQuantity() <= secondItem.getQuantity();
}

std::vector<Item> Controller::filterByCategory(std::string category)
{
	std::vector<Item> filteredItems = {};
	for (auto currentItem : this->allItems)
	{
		if (currentItem.getCategory() == category)
			filteredItems.push_back(currentItem);
	}
	std::sort(filteredItems.begin(), filteredItems.end(), sortByQuantity);
	return filteredItems;
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
