#pragma once
#include "FileWatchlist.h"

class CsvWatchlist :
    public FileWatchlist
{
public:
    CsvWatchlist(const std::string& filename) : FileWatchlist{ filename } {};
    void writeToFile() override;
    void displayWatchlist() override;
};

