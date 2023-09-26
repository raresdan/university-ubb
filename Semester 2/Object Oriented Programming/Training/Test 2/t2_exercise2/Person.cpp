#include "Person.h"
#include <exception>
#include <fstream>

void Person::addAnalysis(MedicalAnalysis* analysisToAdd)
{
	this->allAnalysis.push_back(analysisToAdd);
}

std::vector<MedicalAnalysis*> Person::getAllAnalysis()
{
	return this->allAnalysis;
}

std::vector<MedicalAnalysis*> Person::getAnalysisByMonth(int month)
{
	std::vector<MedicalAnalysis*> analysisByMonth = {};
	for (auto currentAnalysis : this->allAnalysis) 
	{
		if (currentAnalysis->getMonth() == month)
			analysisByMonth.push_back(currentAnalysis);
	}
	return analysisByMonth;
}

bool Person::isIll(int monthToCheck)
{
	std::vector<MedicalAnalysis*> analysisByMonth = this->getAnalysisByMonth(monthToCheck);
	for (const auto& currentAnalysis : this->allAnalysis)
	{
		if (currentAnalysis->isResultOK())
			return false;
	}
	return true;
}

std::vector<MedicalAnalysis*> Person::getAnalysisBetweenDates(std::string dateFrom, std::string dateTo)
{
	std::vector<MedicalAnalysis*> analysisBetweenDates = {};
	for (const auto& currentAnalysis : this->allAnalysis)
	{
		if (currentAnalysis->getDate() >= dateFrom && currentAnalysis->getDate() <= dateTo)
			analysisBetweenDates.push_back(currentAnalysis);
	}
	return analysisBetweenDates;
}

void Person::writeToFile(std::string filename, std::string dateFrom, std::string dateTo)
{
	std::ofstream outputFile{ filename };
	if (!outputFile.is_open())
		throw std::runtime_error{ "File is not opened!" };
	std::vector<MedicalAnalysis*> analysisBetweenDates = this->getAnalysisBetweenDates(dateFrom, dateTo);
	for (const auto& currentAnalysis : analysisBetweenDates)
	{
		outputFile << currentAnalysis->toString();
	}
	outputFile.close();
}
