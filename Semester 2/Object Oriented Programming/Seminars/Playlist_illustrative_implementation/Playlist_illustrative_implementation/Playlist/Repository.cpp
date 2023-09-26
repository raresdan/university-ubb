#include "Repository.h"
#include <string>

using namespace std;

void Repository::addSong(const Song& s)
{
	this->songs.add(s);
}

Song Repository::findByArtistAndTitle(const std::string& artist, const std::string& title)
{
	// search for the song with the given name and artist and return it
	// if not found, return an "empty" Song

	return Song{};
}