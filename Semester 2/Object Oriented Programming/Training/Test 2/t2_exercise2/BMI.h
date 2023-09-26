#pragma once
#include "MedicalAnalysis.h"

class BMI :
    public MedicalAnalysis
{
private:
    double value;
public:
    BMI(double value, std::string date) : value{ value }, MedicalAnalysis{ date } {};
    bool isResultOK() const override;
    std::string toString() const override;
};

