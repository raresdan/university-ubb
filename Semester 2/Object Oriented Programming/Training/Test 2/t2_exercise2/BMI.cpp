#include "BMI.h"
#include <sstream>

bool BMI::isResultOK() const
{
    if (this->value >= 18.5 && this->value <= 25)
        return true;
    return false;
}

std::string BMI::toString() const
{
    std::stringstream stringStream;
    stringStream << "BMI,"
        << "Date: " << this->date << ","
        << "Value: " << this->value << ","
        << "Good Result: " << this->isResultOK() << std::endl;
    return stringStream.str();
}
