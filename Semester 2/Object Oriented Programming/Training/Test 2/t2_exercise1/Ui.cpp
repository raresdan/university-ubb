#include "Ui.h"
#include <iostream>

#define EXIT 0

using namespace std;

void Ui::addDepartment()
{
	std::string type, hospitalName;
	int numberOfDoctors, numberOfPatients;
	int numberOfMothers, numberOfBabies, averaegeGrade;
	cout << "What department do you want to add?(surgery/neonatal)";
	cin.ignore();
	getline(cin, type);

	cout << "Hospital name: ";
	getline(cin, hospitalName);

	cout << "Doctors: ";
	cin >> numberOfDoctors;

	if (type == "surgery")
	{
		cout << "Patients: ";
		cin >> numberOfPatients;
		Surgery* s = new Surgery(hospitalName, numberOfPatients, numberOfDoctors);
		this->controller.addDepartment(s);
	}
	else if (type == "neonatal")
	{
		cout << "Mothers: ";
		cin >> numberOfMothers;
		cout << "Babies: ";
		cin >> numberOfBabies;
		cout << "Average grade: ";
		cin >> averaegeGrade;
		NeonatalUnit* nu = new NeonatalUnit(hospitalName, numberOfMothers, numberOfBabies, numberOfDoctors, averaegeGrade);
		this->controller.addDepartment(nu);
	}

	cout << "Department added!\n";
}

void Ui::showAllDepartments()
{
	for (auto currentDepartment : controller.getAllDepartments())
	{
		cout << currentDepartment->toString();
	}
}

void Ui::showAllEfficientDepartments()
{
	for (auto currentDepartment : controller.getAllEfficientDepartments())
	{
		cout << currentDepartment->toString();
	}
}

void Ui::writeToFile()
{
	std::string filename;
	cout << "To which file do you wanna save?";
	cin.ignore();
	getline(cin, filename);
	try
	{
		controller.writeToFile(filename);
	}
	catch(const std::runtime_error message)
	{
		cout << message.what();
	}
}

void Ui::printMenu()
{
	cout << "Menu\n\n";
	cout << "1 - Add department\n";
	cout << "2 - Show all departments\n";
	cout << "3 - Show efficient departments\n";
	cout << "4 - Save to file\n";
	cout << "0 - EXIT\n";
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
		case 1:
			this->addDepartment();
			break;
		case 2:
			this->showAllDepartments();
			break;
		case 3:
			this->showAllEfficientDepartments();
			break;
		case 4:
			this->writeToFile();
			break;
		case EXIT:
			std::cout << std::endl;
			return;
		default:
			std::cout << "\nInvalid option! Please try again!\n\n";
			break;
		}
	}
}
