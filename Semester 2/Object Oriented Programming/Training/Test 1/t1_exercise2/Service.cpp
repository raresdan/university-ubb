#include "Service.h"
#include <algorithm>

int compareColor(const Car& firstCar, const Car& secondCar)
{
	if (firstCar.getColor() <= secondCar.getColor())
		return 1;
	return 0;
}

int compareManufacturerAndModel(const Car& firstCar, const Car& secondCar)
{
	if (firstCar.getManufacturerName() == secondCar.getManufacturerName())
	{
		if (firstCar.getModel() <= secondCar.getModel())
			return 1;
	}
	else if (firstCar.getManufacturerName() <= secondCar.getManufacturerName())
		return 1;
	return 0;
}

Service::Service(Repository initialCarsRepository)
{
	this->carsRepository = initialCarsRepository;
}

bool Service::addCar(std::string manufacturerName, std::string model, int yearOfFabrication, std::string color)
{
	Car carToAdd{ manufacturerName, model, yearOfFabrication, color };
	return this->carsRepository.addCar(carToAdd);
}

bool Service::removeCar(std::string model, int yearOfFabrication)
{
	Car carToRemove{"", model, yearOfFabrication, ""};
	int indexOfCarToRemove = this->carsRepository.getPosition(carToRemove);
	return this->carsRepository.removeCar(indexOfCarToRemove);
}

std::vector<Car> Service::getAllCars()
{
	std::vector<Car> allCars = this->carsRepository.getAllCars();
	std::sort(allCars.begin(), allCars.end(), compareManufacturerAndModel);
	return allCars;
}

std::vector<Car> Service::getVintageCars()
{
	std::vector<Car> allCars = this->getAllCars();
	std::vector<Car> vintageCars = {};
	for (const auto& currentCar : allCars)
	{
		int yearOfFabrication = currentCar.getYearOfFabrication();
		if ((2023 - yearOfFabrication) >= 45)
			vintageCars.push_back(currentCar);
	}
	std::sort(vintageCars.begin(), vintageCars.end(), compareColor);
	return vintageCars;
}

void Service::initializeRepository()
{
	this->addCar("Fiat", "Bravo", 2007, "red");
	this->addCar("Fiat", "Idea", 2003, "black");
	this->addCar("Audi", "A5", 2007, "blue");
	this->addCar("BMW", "Coupe", 2013, "pink");
	this->addCar("Ford", "Fiesta", 1976, "yellow");
}
