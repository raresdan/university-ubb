#include "Ui.h"
#include <iostream>

#define ADD_CAR 1
#define REMOVE_CAR 2
#define SHOW_CARS 3
#define VINTAGE_CARS 4
#define EXIT 0

Ui::Ui(Service initialService) : service{initialService}
{
}

void Ui::addCar()
{
	std::string manufacturerName = "", model = "", color = "";
	int yearOfFabrication = 0;
	
	std::cout << "Manfacturer: ";
	std::cin.ignore();
	std::getline(std::cin, manufacturerName);

	std::cout << "Model: ";
	std::getline(std::cin, model);

	std::cout << "Year: ";
	std::cin >> yearOfFabrication;

	std::cout << "Color: ";
	std::cin.ignore();
	std::getline(std::cin, color);

	bool checkAdded = this->service.addCar(manufacturerName, model, yearOfFabrication, color);
	if (checkAdded == false)
		std::cout << "Car already exists!";
	else
		std::cout << "Car added succesfully!";
}

void Ui::removeCar()
{
	std::string manufacturerName = "", model = "", color = "";
	int yearOfFabrication = 0;

	std::cout << "Model: ";
	std::cin.ignore();
	std::getline(std::cin, model);

	std::cout << "Year: ";
	std::cin >> yearOfFabrication;

	bool checkRemoved = this->service.removeCar(model, yearOfFabrication);
	if (checkRemoved == false)
		std::cout << "Car doesn't exists!";
	else
		std::cout << "Car removed succesfully!";
}

void Ui::showAllCars()
{
	std::vector<Car> allCars = this->service.getAllCars();
	int index = 1;
	for (const auto& currentCar : allCars)
	{
		std::cout << "#" << index << std::endl;
		std::cout << "Manufacturer: " << currentCar.getManufacturerName() << std::endl;
		std::cout << "Model: " << currentCar.getModel() << std::endl;
		std::cout << "Year: " << currentCar.getYearOfFabrication() << std::endl;
		std::cout << "Color: " << currentCar.getColor() << std::endl;
		std::cout << std::endl;
		index++;
	}
}

void Ui::showVintageCars()
{
	std::vector<Car> vintageCars = this->service.getVintageCars();
	int index = 1;
	for (const auto& currentCar : vintageCars)
	{
		std::cout << "#" << index << std::endl;
		std::cout << "Manufacturer: " << currentCar.getManufacturerName() << std::endl;
		std::cout << "Model: " << currentCar.getModel() << std::endl;
		std::cout << "Year: " << currentCar.getYearOfFabrication() << std::endl;
		std::cout << "Color: " << currentCar.getColor() << std::endl;
		std::cout << std::endl;
		index++;
	}
}

void Ui::printMenu()
{
	std::cout << " Welcome " << std::endl;
	std::cout << std::endl;
	std::cout << "1 - Add a car" << std::endl;
	std::cout << "2 - Remove a car" << std::endl;
	std::cout << "3 - Show all cars" << std::endl;
	std::cout << "4 - Show vintage cars" << std::endl;
	std::cout << "0 - EXIT" << std::endl;
}

void Ui::startApplication()
{
	int optionChosen;
	printMenu();
	while (true)
	{
		std::cout << "\nEnter your option: ";
		std::cin >> optionChosen;
		if (std::cin.fail() || optionChosen < 0 || optionChosen > 4) {
			std::cout << "\nInvalid input! Please enter a valid option.\n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		switch (optionChosen)
		{
		case ADD_CAR:
			this->addCar();
			break;
		case REMOVE_CAR:
			this->removeCar();
			break;
		case SHOW_CARS:
			this->showAllCars();
			break;
		case VINTAGE_CARS:
			this->showVintageCars();
			break;
		case EXIT:
			std::cout << "Application exited successfully!";
			std::cout << std::endl;
			return;
		default:
			std::cout << "\nInvalid option! Please try again!\n\n";
			break;
		}
	}
}
