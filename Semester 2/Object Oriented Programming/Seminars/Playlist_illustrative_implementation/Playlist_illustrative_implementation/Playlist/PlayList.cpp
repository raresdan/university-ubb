#include "PlayList.h"


PlayList::PlayList()
{
	this->current = 0;
}

void PlayList::add(const Song& song)
{
	this->songs.add(song);
}

Song PlayList::getCurrentSong()
{
	// TODO
	return Song{};
}

void PlayList::play()
{
	// TODO
}

void PlayList::next()
{
	// TODO
}

bool PlayList::isEmpty()
{
	return this->songs.getSize() == 0;
}