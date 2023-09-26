#pragma once
#include "Watchlist.h"

class FileWatchlist :
    public Watchlist
{
protected:
    std::string filename;
public:
    FileWatchlist(const std::string& filename) : filename{ filename } {};
    virtual void writeToFile() = 0;
    virtual void displayWatchlist() = 0;
    virtual ~FileWatchlist() {}
};

