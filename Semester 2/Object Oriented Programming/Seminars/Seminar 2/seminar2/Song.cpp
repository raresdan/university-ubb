#include "Song.h"

Song::Song(const std::string& _artist, const std::string& _title, 
	int _duration): artist{_artist}, title{_title}, duration{_duration}
{
	/*
	* definition above is the same as writting this:
 
	this->artist = _artist;
	this->title = _title;
	this->duration = _duration;
	*/
}

std::string Song::getTitle()
{
	return this->title;
}

void Song::setTitle(const std::string& title)
{
}
