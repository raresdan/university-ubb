#pragma once
#include "FilePlaylist.h"
class CsvPlaylist :
    public FilePlaylist
{
public:
    CsvPlaylist(const std::string& filename) : FilePlaylist{ filename } {};
    void writeToFile() override;
    void displayPlaylist() override;
};

