#pragma once
#include "HospitalDepartment.h"

class Surgery :
    public HospitalDepartment
{
private:
    int numberOfPatients;
public:
    Surgery(std::string name, int patients, int doctors) :
        numberOfPatients{ patients }, HospitalDepartment{ name, doctors } {};
    bool isEfficient() override;
    std::string toString() override;
};

