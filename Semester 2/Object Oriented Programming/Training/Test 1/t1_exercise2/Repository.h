#pragma once
#include <vector>
#include "Car.h"

class Repository
{
private:
	std::vector<Car> allCars;
public:
	Repository(std::vector<Car> initialCars = {});
	std::vector<Car> getAllCars();
	bool addCar(Car carToAdd);
	bool removeCar(int indexOfCarToRemove);
	int getPosition(Car carToGetPosition);
};

