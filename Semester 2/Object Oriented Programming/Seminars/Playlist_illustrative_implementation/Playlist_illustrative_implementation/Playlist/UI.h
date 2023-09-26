#pragma once
#include "Service.h"

class UI
{
private:
	Service service;

public:
	UI(const Service& s) : service(s) {}

	void run();

private:
	static void printMenu();
	static void printRepositoryMenu();
	static void printPlayListMenu();

	void addSongToRepo();
	void displayAllSongsRepo();
	void addSongToPlaylist();
	void addAllSongsByArtistToPlaylist();
};

