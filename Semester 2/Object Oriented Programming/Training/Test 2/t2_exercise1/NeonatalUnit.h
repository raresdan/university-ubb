#pragma once
#include "HospitalDepartment.h"

class NeonatalUnit :
    public HospitalDepartment
{
private:
    int numberOfMothers;
    int numberOfNewborns;
public:
    double averageGrade;
    NeonatalUnit(std::string name, int mothers, int babies, int doctors, double averageGrade) : numberOfMothers{ mothers },
        numberOfNewborns{ babies },
        averageGrade{averageGrade},
        HospitalDepartment{name, doctors} {};
    bool isEfficient() override;
    std::string toString() override;
};

