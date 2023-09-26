#include "JSONPlayList.h"

void JSONPlayList::writeSongToJSON(std::ostream& os, const Song& s)
{
	os << "{\n"
		<< "\t\"artist\":\"" << s.getArtist() << "\",\n"
		<< "\t\"title\":\"" << s.getTitle() << "\""
		<< "\n}";
}

void JSONPlayList::writeToFile()
{
	std::ofstream fout{ filename };
	if (!fout.is_open())
		throw std::runtime_error{ "File is not opened!" };
	fout << "{\"songs\":[\n";

	for (int i = 0; i < songs.size() - 1; i++)
	{
		this->writeSongToJSON(fout, songs[i]);
		fout << ",\n";
	}

	this->writeSongToJSON(fout, songs[songs.size() - 1]);
	fout << "\n]}\n";

	fout.close();
}

void JSONPlayList::displayPlaylist()
{
	ShellExecuteA(NULL,
		"open",
		"C:\\Program Files\\Notepad++\\notepad++.exe",
		filename.c_str(),
		NULL,
		SW_MAXIMIZE
	);
}