#pragma once
#include "Service.h"

class Ui
{
private:
	Service service;
public:
	Ui(Service initialService);
	void addCar();
	void removeCar();
	void showAllCars();
	void showVintageCars();
	void printMenu();
	void startApplication();
};

