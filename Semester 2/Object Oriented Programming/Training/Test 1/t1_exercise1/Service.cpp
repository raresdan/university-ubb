#include "Service.h"
#include <algorithm>

Service::Service(Repository initialBillsRepository)
{
	this->billsRepository = initialBillsRepository;
}

std::vector<Bill> Service::getAllBills()
{
	return this->billsRepository.getAllBills();
}

void Service::initializeRepository()
{
	this->addBill("0A33455X", "Digi Sport", { 15,4,2016 }, 75.00, false);
	this->addBill("EED36677", "E-On", { 16,3,2016 }, 122.00, true);
	this->addBill("X990TTRR", "Orange", { 18,4,2016 }, 46.00, false);
	this->addBill("1234RR55", "Vodafone", { 20,4,2016 }, 23.00, false);
	this->addBill("TRE3EERR", "Tcomm", { 21,4,2016 }, 10.00, true);
}

bool Service::addBill(std::string serialNumber, std::string companyName, Date dueDate, float sumToPay, bool isPaid)
{
	Bill billToAdd{ serialNumber, companyName, dueDate, sumToPay, isPaid };
	return this->billsRepository.addBill(billToAdd);
}

bool Service::removeBill(std::string serialNumber)
{
	Bill billToRemove{ serialNumber, "", {0,0,0}, 0.0, false };
	int indexOfBillToRemove = this->billsRepository.getBillPosition(billToRemove);
	return this->billsRepository.removeBill(indexOfBillToRemove);
}

void Service::sortBillsByDueDate()
{
}

float Service::calculateTotalOfUnpaidBills()
{
	float totalSum = 0.0;
	for (const auto& currentBill : this->getAllBills())
	{
		if (currentBill.getPaidStatus() == false)
			totalSum += currentBill.getSumToPay();
	}
	return totalSum;
}
