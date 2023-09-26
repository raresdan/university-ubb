#pragma once
#include "Item.h"
#include <vector>

class Controller
{
private:
	std::vector<Item> allItems;
	std::string filename;
public:
	Controller(std::string filename, std::vector<Item> initialItems = {}) :
		filename{ filename }, allItems{ initialItems } {
		this->readFromFile();
	}
	std::vector<Item> getAllItems();
	std::vector<Item> searchItem(std::string searchedString = "");
	std::vector<Item> filterByCategory(std::string category);
	void readFromFile();
};

