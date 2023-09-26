#pragma once
#include "HospitalDepartment.h"

class Surgery :
    public HospitalDepartment
{
private:
    int numberOfPatients;
public:
    Surgery(std::string hospitalName, int numberOfDoctors, int numberOfPatients) :
        HospitalDepartment{ hospitalName, numberOfDoctors },
        numberOfPatients{ numberOfPatients } {};
    bool isEfficient();
    std::string toString();
};

