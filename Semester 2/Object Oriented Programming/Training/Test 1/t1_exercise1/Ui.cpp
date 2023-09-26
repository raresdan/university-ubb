#include "Ui.h"
#include <iostream>
#include <string>

#define REMOVE_BILL 1
#define DISPLAY_BILLS 2
#define SORT_BILLS 3
#define UNPAID_BILLS_TOTAL 4
#define EXIT 0

Ui::Ui(Service initialService)
{
	this->service = initialService;
}

void Ui::removeBill()
{
	std::string serialNumber = "";
	std::cout << "Serial Number of the bill to remove: ";
	std::cin.ignore();
	std::getline(std::cin, serialNumber);
	bool checkRemoved = this->service.removeBill(serialNumber);
	if (checkRemoved == false)
		std::cout << "No such bill exists!\n";
	else
		std::cout << "Bill removed!\n";
}

void Ui::displayAllBills()
{
	int index = 1;
	std::vector<Bill> allBills = this->service.getAllBills();
	for (const auto& currentBill : allBills)
	{
		Date currentBillDate = currentBill.getDueDate();
		bool currentBillPaidStatus = currentBill.getPaidStatus();
		std::cout << "#" << index << std::endl;
		std::cout << "Serial Number: " << currentBill.getSerialNumber() << std::endl;
		std::cout << "Company: " << currentBill.getCompanyName() << std::endl;
		std::cout << "Due: " << currentBillDate.day << "." << currentBillDate.month << "." << currentBillDate.year << std::endl;
		std::cout << "Amount: " << currentBill.getSumToPay() << " RON" << std::endl;
		if (currentBillPaidStatus == false)
			std::cout << "Not Paid" << std::endl;
		else
			std::cout << "Paid" << std::endl;
		std::cout << std::endl;
		index++;
	}
}

void Ui::sortAllUnpaidBillsByDueDate()
{
	this->service.sortBillsByDueDate();
}

void Ui::calculateTotalOfUnpaidBills()
{
	float totalSum = this->service.calculateTotalOfUnpaidBills();
	std::cout << "You still have to pay: " << totalSum << " RON";
	std::cout << std::endl;
}

void Ui::printMenu()
{
	std::cout << "\nWelcome!\n\n";
	std::cout << "1. Remove a bill\n";
	std::cout << "2. Display all bills\n";
	std::cout << "3. Sort unpaid bills by due date\n";
	std::cout << "4. Calculate total of unpaid bills\n";
	std::cout << "0. Exit application\n";
}

void Ui::startApplication()
{
	int optionChosen;
	this->printMenu();
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
		case REMOVE_BILL:
			this->removeBill();
			break;
		case DISPLAY_BILLS:
			this->displayAllBills();
			break;
		case SORT_BILLS:
			this->sortAllUnpaidBillsByDueDate();
			break;
		case UNPAID_BILLS_TOTAL:
			this->calculateTotalOfUnpaidBills();
			break;
		case EXIT:
			std::cout << "Application exited sucessfully!" << std::endl;
			return;
		default:
			std::cout << "\nInvalid option! Please try again!\n\n";
			break;
		}
	}
}
