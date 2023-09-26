#include "BP.h"
#include <sstream>

bool BP::isResultOK() const
{
    if (this->systolicValue >= 90 && this->systolicValue <= 119 && this->diastolicValue >= 60 && this->diastolicValue <= 79)
        return true;
    return false;
}

std::string BP::toString() const
{
    std::stringstream stringStream;
    stringStream << "BP,"
        << "Date: " << this->date << ","
        << "Systolic: " << this->systolicValue << ","
        << "Diastolic: " << this->diastolicValue << ","
        << "Good Result: " << this->isResultOK() << std::endl;
    return stringStream.str();
}
