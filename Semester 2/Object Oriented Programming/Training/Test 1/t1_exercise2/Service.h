#pragma once
#include "Repository.h"

class Service
{
private:
	Repository carsRepository;
public:
	Service(Repository initialCarsRepository);
	bool addCar(std::string manufacturerName, std::string model, int yearOfFabrication, std::string color);
	bool removeCar(std::string model, int yearOfFabrication);
	std::vector<Car> getAllCars();
	std::vector<Car> getVintageCars();
	void initializeRepository();
};

