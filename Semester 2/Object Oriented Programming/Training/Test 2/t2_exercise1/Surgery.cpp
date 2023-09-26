#include "Surgery.h"

bool Surgery::isEfficient()
{
    if ((this->numberOfPatients / this->numberOfDoctors) >= 2)
        return true;
    return false;
}

std::string Surgery::toString()
{
    std::stringstream stringStream;
    stringStream << "Surgery "
        << this->hospitalName << " " 
        << this->numberOfDoctors << " " 
        << this->numberOfPatients << " "
        << this->isEfficient() << std::endl;
    return stringStream.str();
}
