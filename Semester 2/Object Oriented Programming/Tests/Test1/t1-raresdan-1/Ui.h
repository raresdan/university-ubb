#pragma once
#include "Service.h"

class Ui
{
private:
	Service service;
public:
	Ui(Service initialService);
	void addPlayer();
	void displayAllPlayers();
	void displayAllPlayersOfTeam();
	void printMenu();
	void startApplication();
};

