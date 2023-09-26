#pragma once
#include "MedicalAnalysis.h"

class BP :
    public MedicalAnalysis
{
private:
    int systolicValue;
    int diastolicValue;
public: 
    BP(int systolicValue, int diastolicValue, std::string date) : 
        systolicValue{ systolicValue },
        diastolicValue{diastolicValue},
        MedicalAnalysis { date } {};
    bool isResultOK() const override;
    std::string toString() const override;
};

