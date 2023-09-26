#pragma once
#include <string>
#include <vector>
#include "MedicalAnalysis.h"
#include "BP.h"
#include "BMI.h"

class Person
{
private:
	std::vector<MedicalAnalysis*> allAnalysis;
	std::string name;
public:
	Person(std::string name, std::vector<MedicalAnalysis*> initialAnalysis = {}) : name{ name } 
	{
		BP* analysis = new BP(100, 59, "2023.05.14");
		BMI* analysis2 = new BMI(20, "2023.05.15");
		this->addAnalysis(analysis);
		this->addAnalysis(analysis2);
	};
	void addAnalysis(MedicalAnalysis* analysisToAdd);
	std::vector<MedicalAnalysis*> getAllAnalysis();
	std::vector<MedicalAnalysis*> getAnalysisByMonth(int month);
	bool isIll(int monthToCheck);
	std::vector<MedicalAnalysis*> getAnalysisBetweenDates(std::string dateFrom, std::string dateTo);
	void writeToFile(std::string filename, std::string dateFrom, std::string dateTo);
};

