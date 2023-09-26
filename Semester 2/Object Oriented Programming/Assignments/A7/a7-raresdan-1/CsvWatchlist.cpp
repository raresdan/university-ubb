#include "CsvWatchlist.h"
#include <fstream>
#include <exception>
#include <Windows.h>
#include <shellapi.h>

void CsvWatchlist::writeToFile()
{
	std::ofstream outputFile{ filename };
	if (!outputFile.is_open())
		throw std::runtime_error{ "File is not opened!" };
	for (const auto& currentTutorial : allTutorials)
	{
		outputFile << currentTutorial;
	}
	outputFile.close();
}

void CsvWatchlist::displayWatchlist()
{
	ShellExecuteA(NULL,
		"open",
		"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE",
		filename.c_str(),
		NULL,
		SW_MAXIMIZE
	);
}
