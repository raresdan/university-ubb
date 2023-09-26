#include "Ui.h"
#include <iostream>

#define EXIT 0
#define ADD_DEPARTMENT 1
#define SHOW_DEPARTMENTS 2
#define SHOW_EFFICIENT_DEPARTMENTS 3
#define SAVE_TO_FILE 4

void Ui::addDepartment()
{
	std::string departmentType, hosptialName;
	int numberOfDoctors, numberOfPatients;
	double averageGrade;

	std::cout << "What type of department do you want to add? (surgery/neonatal) " << std::endl;
	std::cin.ignore();
	getline(std::cin, departmentType);

	std::cout << "Hospital name: ";
	getline(std::cin, hosptialName);

	std::cout << "Number of doctors: ";
	std::cin >> numberOfDoctors;

	if (departmentType == "surgery")
	{
		std::cout << "Number Of Patients: ";
		std::cin >> numberOfPatients;

		Surgery* surgeryToAdd = new Surgery{ hosptialName, numberOfDoctors, numberOfPatients };
		this->controller.addDepartment(surgeryToAdd);
	}
	else if (departmentType == "neonatal")
	{
		std::cout << "Average Grade: ";
		std::cin >> averageGrade;

		NeonatalUnit* neonatalToAdd = new NeonatalUnit{ hosptialName, numberOfDoctors, averageGrade };
		this->controller.addDepartment(neonatalToAdd);
	}
	std::cout << "Department added!\n\n";
}

void Ui::showAllDepartments()
{
	for (auto currentDepartment : this->controller.getAllDepartments())
	{
		std::cout << currentDepartment->toString();
	}
}

void Ui::showEfficientDepartments()
{
	for (auto currentDepartment : this->controller.getAllEfficientDepartments())
	{
		std::cout << currentDepartment->toString();
	}
}

void Ui::saveToFile()
{
	std::string filename;
	std::cout << "Where do you want to save? ";
	std::cin.ignore();
	getline(std::cin, filename);
	try
	{
		this->controller.writeToFile(filename);
	}
	catch (const std::runtime_error message)
	{
		std::cout << message.what();
	}
	std::cout << "File saved succesfully!\n";
}

void Ui::printMenu()
{
	std::cout << "MENU\n\n";
	std::cout << "1 - Add new department\n";
	std::cout << "2 - Show all departments\n";
	std::cout << "3 - Show efficient departments\n";
	std::cout << "4 - Save to file\n";
	std::cout << "0 - EXIT\n\n";
}

void Ui::startApplication()
{
	this->printMenu();
	int optionChosen;
	while(true)
	{
		std::cout << std::endl;
		std::cout << "Enter your option: ";
		std::cin >> optionChosen;
		std::cout << std::endl;

			switch (optionChosen)
			{
			case ADD_DEPARTMENT:
				this->addDepartment();
				break;
			case SHOW_DEPARTMENTS:
				this->showAllDepartments();
				break;
			case SHOW_EFFICIENT_DEPARTMENTS:
				this->showEfficientDepartments();
				break;
			case SAVE_TO_FILE:
				this->saveToFile();
				break;
			case EXIT:
				std::cout << "Application exited\n";
				return;
			default:
				std::cout << "Invalid option! Try again!\n";
				break;
			}
		
	}
}
