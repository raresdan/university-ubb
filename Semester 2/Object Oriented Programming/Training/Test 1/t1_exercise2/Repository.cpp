#include "Repository.h"

Repository::Repository(std::vector<Car> initialCars)
{
	this->allCars = initialCars;
}

std::vector<Car> Repository::getAllCars()
{
	return this->allCars;
}

bool Repository::addCar(Car carToAdd)
{
	auto iterator = std::find(this->allCars.begin(), this->allCars.end(), carToAdd);
	if (iterator != this->allCars.end())
		return false;
	this->allCars.push_back(carToAdd);
	return true;
}

bool Repository::removeCar(int indexOfCarToRemove)
{
	if (indexOfCarToRemove < 0 || indexOfCarToRemove > this->allCars.size())
		return false;
	this->allCars.erase(this->allCars.begin() + indexOfCarToRemove);
	return true;
}

int Repository::getPosition(Car carToGetPosition)
{
	auto iterator = std::find(this->allCars.begin(), this->allCars.end(), carToGetPosition);
	if (iterator == this->allCars.end())
		return -1;
	return std::distance(this->allCars.begin(), iterator);
}
