#include "CsvPlaylist.h"
#include <fstream>
#include <exception>
#include <Windows.h>
#include <shellapi.h>

void CsvPlaylist::writeToFile()
{
	std::ofstream fout{filename};
	if (!fout.is_open())
		throw std::runtime_error{ "File is not opened!" };
	for (const auto& s : songs)
	{
		fout << s;
	}
	fout.close();
}

void CsvPlaylist::displayPlaylist()
{
	ShellExecuteA(NULL,
		"open",
		"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE",
		filename.c_str(),
		NULL,
		SW_MAXIMIZE
	);
}
