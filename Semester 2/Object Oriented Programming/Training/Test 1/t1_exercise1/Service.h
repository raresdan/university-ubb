#pragma once
#include "Repository.h"

class Service
{
private:
	Repository billsRepository;

public:
	Service(Repository initialBillsRepository = {});
	std::vector<Bill> getAllBills();
	void initializeRepository();
	bool addBill(std::string serialNumber,
		std::string companyName,
		Date dueDate,
		float sumToPay,
		bool isPaid);
	bool removeBill(std::string serialNumber);
	void sortBillsByDueDate();
	float calculateTotalOfUnpaidBills();
};

