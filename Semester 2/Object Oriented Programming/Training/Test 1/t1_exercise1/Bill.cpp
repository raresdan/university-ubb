#include "Bill.h"

Bill::Bill(std::string serialNumber, std::string companyName, Date dueDate, float sumToPay, bool isPaid)
{
    this->serialNumber = serialNumber;
    this->companyName = companyName;
    this->dueDate = dueDate;
    this->sumToPay = sumToPay;
    this->isPaid = isPaid;
}

std::string Bill::getSerialNumber() const
{
    return this->serialNumber;
}

std::string Bill::getCompanyName() const
{
    return this->companyName;
}

Date Bill::getDueDate() const
{
    return this->dueDate;
}

float Bill::getSumToPay() const
{
    return this->sumToPay;
}

bool Bill::getPaidStatus() const
{
    return this->isPaid;
}

void Bill::setSerialNumber(std::string newSerialNumber)
{
    this->serialNumber = newSerialNumber;
}

void Bill::setCompanyName(std::string newCompanyName)
{
    this->companyName = newCompanyName;
}

void Bill::setDueDate(Date newDate)
{
    this->dueDate = newDate;
}

void Bill::setSumToPay(float newSum)
{
    this->sumToPay = newSum;
}

void Bill::setPaidStatus(bool newStatus)
{
    this->isPaid = newStatus;
}

bool Bill::operator==(const Bill& billToCompare)
{
    if (this->serialNumber == billToCompare.getSerialNumber())
        return true;
    return false;
}

void Bill::operator=(const Bill& billToCopy)
{
    this->serialNumber = billToCopy.getSerialNumber();
    this->companyName = billToCopy.getCompanyName();
    this->dueDate = billToCopy.getDueDate();
    this->sumToPay = billToCopy.getSumToPay();
    this->isPaid = billToCopy.getPaidStatus();
}
