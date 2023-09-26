#include "Surgery.h"
#include <sstream>

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
        << "Name: " << this->hospitalName << " "
        << "Doctors: " << this->numberOfDoctors << " "
        << "Patients: " << this->numberOfPatients << " "
        << "Efficient: " << this->isEfficient() << std::endl;
    return stringStream.str();
}
