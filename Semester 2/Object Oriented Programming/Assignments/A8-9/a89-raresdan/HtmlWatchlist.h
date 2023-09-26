#pragma once
#include "FileWatchlist.h"
#include <iostream>
#include <fstream>

class HtmlWatchlist :
    public FileWatchlist
{
private:
    void writeTutorialToHTML(std::ostream& outputFile, const Tutorial& tutorialToWrite);
public:
    HtmlWatchlist(const std::string& filename) : FileWatchlist{ filename } {	
	};
    void writeToFile() override;
    void displayWatchlist() override;
};

