#pragma once
#include "PlayList.h"
class FilePlaylist :
    public PlayList
{
protected:
    std::string filename;
public:
    FilePlaylist(const std::string& filename) : filename{ filename } {};
    virtual void writeToFile() = 0;
    virtual void displayPlaylist() = 0;

    virtual ~FilePlaylist() {}
};

