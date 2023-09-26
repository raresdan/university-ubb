#pragma once
#include "Service.h"


class Ui
{
private:
	Service service;
public:
	Ui(Service initialService);
	void removeBill();
	void displayAllBills();
	void sortAllUnpaidBillsByDueDate();
	void calculateTotalOfUnpaidBills();
	void printMenu();

	void startApplication();
};

