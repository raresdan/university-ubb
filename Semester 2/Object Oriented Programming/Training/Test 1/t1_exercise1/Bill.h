#pragma once
#include <string>

typedef struct
{
	int day, month, year;
}Date;

class Bill
{
private:
	std::string serialNumber;
	std::string companyName;
	Date dueDate;
	float sumToPay;
	bool isPaid;

public:
	Bill() : serialNumber(""), companyName(""), dueDate{ 0,0,0 }, sumToPay(0.0), isPaid(false) {}
	Bill(std::string serialNumber, 
		std::string companyName, 
		Date dueDate, 
		float sumToPay, 
		bool isPaid);
	
	// Getters
	std::string getSerialNumber() const;
	std::string getCompanyName() const;
	Date getDueDate() const;
	float getSumToPay() const;
	bool getPaidStatus() const;

	//Setters
	void setSerialNumber(std::string newSerialNumber);
	void setCompanyName(std::string newCompanyName);
	void setDueDate(Date newDate);
	void setSumToPay(float newSum);
	void setPaidStatus(bool newStatus);

	//Operators
	bool operator==(const Bill& billToCompare);
	void operator=(const Bill& billToCopy);
};

