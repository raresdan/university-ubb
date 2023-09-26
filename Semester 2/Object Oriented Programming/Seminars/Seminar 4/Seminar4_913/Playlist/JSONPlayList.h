#pragma once
#include <string>
#include "FilePlaylist.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <Windows.h>
#include <shellapi.h>


class JSONPlayList :
    public FilePlaylist
{
private:
    void writeSongToJSON(std::ostream& os, const Song& s);

public:
    JSONPlayList(const std::string& filename) : FilePlaylist{ filename } {};
    void writeToFile() override;
    void displayPlaylist() override;
};

