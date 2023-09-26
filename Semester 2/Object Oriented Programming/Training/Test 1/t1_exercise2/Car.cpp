#include "Car.h"

Car::Car(std::string manufacturerName, std::string model, int yearOfFabrication, std::string color)
{
	this->manufacturerName = manufacturerName;
	this->model = model;
	this->yearOfFabrication = yearOfFabrication;
	this->color = color;
}

std::string Car::getManufacturerName() const
{
	return this->manufacturerName;
}

std::string Car::getModel() const
{
	return this->model;
}

int Car::getYearOfFabrication() const
{
	return this->yearOfFabrication;
}

std::string Car::getColor() const
{
	return this->color;
}

void Car::setManufacturerName(std::string newName)
{
	this->manufacturerName = newName;
}

void Car::setModel(std::string newModel)
{
	this->model = newModel;
}

void Car::setYearOfFabrication(int newYear)
{
	this->yearOfFabrication = newYear;
}

void Car::setColor(std::string newColor)
{
	this->color = newColor;
}

bool Car::operator==(const Car& carToCompare)
{
	if (this->model == carToCompare.model && this->yearOfFabrication == carToCompare.yearOfFabrication)
		return true;
	return false;
}

void Car::operator=(const Car& carToCopy)
{
	this->manufacturerName = carToCopy.manufacturerName;
	this->model = carToCopy.model;
	this->yearOfFabrication = carToCopy.yearOfFabrication;
	this->color = carToCopy.color;
}
