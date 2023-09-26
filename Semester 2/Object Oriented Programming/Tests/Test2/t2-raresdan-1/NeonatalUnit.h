#pragma once
#include "HospitalDepartment.h"

class NeonatalUnit :
    public HospitalDepartment
{
public:
    double averageGrade;
    NeonatalUnit(std::string hospitalName, int numberOfDoctors, double averageGrade) :
        HospitalDepartment{ hospitalName, numberOfDoctors },
        averageGrade{ averageGrade } {};
    bool isEfficient();
    std::string toString();
};

