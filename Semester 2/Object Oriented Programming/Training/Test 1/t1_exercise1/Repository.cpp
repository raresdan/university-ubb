#include "Repository.h"

Repository::Repository(std::vector<Bill> initialBills)
{
	this->allBills = initialBills;
}

std::vector<Bill> Repository::getAllBills()
{
	return this->allBills;
}

bool Repository::addBill(Bill billToAdd)
{
	auto iterator = std::find(this->allBills.begin(), this->allBills.end(), billToAdd);
	if (iterator != this->allBills.end())
		return false;
	this->allBills.push_back(billToAdd);
	return true;
}

bool Repository::removeBill(int indexOfBillToRemove)
{
	if (indexOfBillToRemove < 0 || indexOfBillToRemove > this->allBills.size())
		return false;
	this->allBills.erase(this->allBills.begin() + indexOfBillToRemove);
}

int Repository::getBillPosition(Bill billToGetPosition)
{
	auto iterator = std::find(this->allBills.begin(), this->allBills.end(), billToGetPosition);
	if (iterator == this->allBills.end())
		return -1;
	return std::distance(this->allBills.begin(), iterator);
}
