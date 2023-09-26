#pragma once
#include "Service.h"

class UI
{
private:
	Service ctrl;

public:
	UI(const Service& c) : ctrl(c) {}

	void run();

private:
	static void printMenu();
	static void printRepositoryMenu();
	static void printPlayListMenu();

	void addSongToRepo();
	void displayAllSongsRepo();
	void addSongToPlaylist();
	void addAllSongsByArtistToPlaylist();
	void savePlaylistToFile();
};

