#pragma once
#include <string>

class Item
{
private:
	std::string category;
	std::string name;
	int quantity;
public:
	Item() : category(""), name(""), quantity(0) {};
	Item(std::string category, std::string name, int quantity) :
		category{ category },
		name{ name },
		quantity{ quantity } {};
	std::string getCategory() { return this->category; }
	std::string getName() { return this->name; }
	int getQuantity() { return this->quantity; }

	friend std::istream& operator>>(std::istream& inputStream, Item& itemToRead);
	std::string toString();
};

