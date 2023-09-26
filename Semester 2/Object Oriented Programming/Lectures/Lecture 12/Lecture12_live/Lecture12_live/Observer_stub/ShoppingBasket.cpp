#include "ShoppingBasket.h"

void ShoppingBasket::addProduct(const Product& prod)
{
	this->products.push_back(prod);
	this->notify();
}

std::vector<Product> ShoppingBasket::getAll() const
{
	return this->products;
}
