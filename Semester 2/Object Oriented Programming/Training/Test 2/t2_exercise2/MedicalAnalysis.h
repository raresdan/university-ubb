#pragma once
#include <string>

class MedicalAnalysis
{
protected:
	std::string date;
public:
	MedicalAnalysis(std::string date) : date{ date } {};
	int getMonth() const;
	std::string getDate() const;
	virtual bool isResultOK() const = 0;
	virtual std::string toString() const = 0;
};

