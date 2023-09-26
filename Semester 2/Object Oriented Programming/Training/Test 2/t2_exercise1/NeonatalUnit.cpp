#include "NeonatalUnit.h"

bool NeonatalUnit::isEfficient()
{
    if (this->averageGrade > 8.5 && this->numberOfNewborns > this->numberOfMothers)
        return true;
    return false;
}

std::string NeonatalUnit::toString()
{
    std::stringstream stringStream;
    stringStream << "Neonatal "
        << this->hospitalName << " "
        << this->numberOfDoctors << " "
        << this->numberOfMothers << " "
        << this->numberOfNewborns << " "
        << this->averageGrade << " "
        << this->isEfficient() << std::endl;
    return stringStream.str();
}
