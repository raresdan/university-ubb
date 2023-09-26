#include "MedicalAnalysis.h"

int MedicalAnalysis::getMonth() const
{
    int month = stoi(this->date.substr(5, 2));
    return month;
}

std::string MedicalAnalysis::getDate() const
{
    return this->date;
}
