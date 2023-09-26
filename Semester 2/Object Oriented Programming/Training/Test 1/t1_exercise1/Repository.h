#pragma once
#include <vector>
#include "Bill.h"

class Repository
{
private:
	std::vector<Bill> allBills;
public:
	Repository(std::vector<Bill> initialBills = {});
	std::vector<Bill> getAllBills();
	bool addBill(Bill billToAdd);
	bool removeBill(int indexOfBillToRemove);
	int getBillPosition(Bill billToGetPosition);
};

