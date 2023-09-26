#include "Ui.h"
#include <iostream>

#define ADD_ANALYSIS 1
#define DISPLAY_ANALYSIS 2
#define ILLNESS_STATUS 3
#define SAVE_TO_FILE 4
#define EXIT 0

void Ui::addAnalysis()
{
	std::string type = "", date = "";
	std::cout << "What type of analysis do you want to add? (BMI/BP)\n";
	std::cin.ignore();
	getline(std::cin, type);

	if (type == "BP")
	{
		int systolic = 0, diastolic = 0;
		std::cout << "Systolic: ";
		std::cin >> systolic;

		std::cout << "Diastolic: ";
		std::cin >> diastolic;

		std::cout << "Date (yyyy.mm.dd):";
		std::cin.ignore();
		getline(std::cin, date);

		BP* BPAnalysisToAdd = new BP(systolic, diastolic, date);
		person.addAnalysis(BPAnalysisToAdd);
	}
	else if (type == "BMI")
	{
		int value;
		std::cout << "Value: ";
		std::cin >> value;

		std::cout << "Date (yyyy.mm.dd):";
		std::cin.ignore();
		getline(std::cin, date);

		BMI* BMIAnalysisToAdd = new BMI(value, date);
		person.addAnalysis(BMIAnalysisToAdd);
	}
	std::cout << "Analysis successfully added!\n";
}

void Ui::displayAllAnalysis()
{
	int index = 1;
	for (const auto& currentAnalysis : person.getAllAnalysis())
	{
		std::cout << "#" << index << " " << currentAnalysis->toString();
		index++;
	}
}

void Ui::checkIllness()
{
	int currentMonth;
	std::cout << "Current Month: ";
	std::cin >> currentMonth;

	bool isIll = person.isIll(currentMonth);
	if (isIll == true)
		std::cout << "Person is ill. Consult medical assistance!\n";
	else
		std::cout << "Person is healthy. Keep it like this!\n";
}

void Ui::saveToFile()
{
	std::string filename,fromDate,toDate;
	std::cout << "Enter file you want to save analysis to: ";
	std::cin.ignore();
	getline(std::cin, filename);

	std::cout << "From date: ";
	std::cin >> fromDate;

	std::cout << "To date: ";
	std::cin >> toDate;

	try
	{
		person.writeToFile(filename, fromDate, toDate);
	}
	catch (const std::runtime_error message)
	{
		std::cout << message.what() << std::endl;
	}

	std::cout << "File successfully written!\n";
}

void Ui::printMenu()
{
	std::cout << "MENU\n\n";
	std::cout << "1 - Add new analysis\n";
	std::cout << "2 - Display all analysis\n";
	std::cout << "3 - Illness status\n";
	std::cout << "4 - Save to file\n";
	std::cout << "0 - EXIT\n";
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
		case ADD_ANALYSIS:
			this->addAnalysis();
			break;
		case DISPLAY_ANALYSIS:
			this->displayAllAnalysis();
			break;
		case ILLNESS_STATUS:
			this->checkIllness();
			break;
		case SAVE_TO_FILE:
			this->saveToFile();
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
