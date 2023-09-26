#include "NeonatalUnit.h"
#include <sstream>

bool NeonatalUnit::isEfficient()
{
    if (this->averageGrade > 8.5)
        return true;
    return false;
}

std::string NeonatalUnit::toString()
{
    std::stringstream stringStream;
    stringStream << "Neonatal-Unit "
        << "Name: " << this->hospitalName << " "
        << "Doctors: " << this->numberOfDoctors << " "
        << "Average Grade: " << this->averageGrade << " "
        << "Efficient: " << this->isEfficient() << std::endl;
    return stringStream.str();
}
