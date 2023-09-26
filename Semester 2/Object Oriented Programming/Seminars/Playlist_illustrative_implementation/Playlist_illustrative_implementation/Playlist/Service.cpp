#include "Service.h"

DynamicVector Service::getAllSongsInRepo() const
{
	return this->repo.getSongs();
}

void Service::addSongToRepository(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song s{ artist, title, Duration{minutes, seconds}, source };
	this->repo.addSong(s);
}

void Service::addSongToPlaylist(const Song& song)
{
	this->playList.add(song);
}

void Service::addAllSongsByArtistToPlaylist(const std::string& artist)
{
	// TODO
}

void Service::startPlaylist()
{
	this->playList.play();
}

void Service::nextSongPlaylist()
{
	this->playList.next();
}