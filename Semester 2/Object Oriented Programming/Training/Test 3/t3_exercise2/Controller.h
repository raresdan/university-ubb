#pragma once
#include "Item.h"
#include <vector>

class Controller
{
private:
	std::vector<Item> allItems;
	std::string filename;
public:
	Controller(std::string filename,std::vector<Item> initalItems = {}):
		filename{ filename }, allItems{ initalItems } {
		this->readFromFile();
	};
	std::vector<Item> getAllItems();
	void deleteItem(std::string category, std::string name);
	void filterItems(std::string category);
	void readFromFile();
};

