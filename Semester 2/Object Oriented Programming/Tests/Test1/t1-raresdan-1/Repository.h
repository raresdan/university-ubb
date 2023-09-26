#pragma once
#include "Player.h"
#include <vector>

class Repository
{
private:
	std::vector<Player> allPlayers;
public:
	Repository(std::vector<Player> initialPlayers);
	std::vector<Player> getAllPlayers();
	bool addPlayer(Player playerToAdd);
	int getPositionOfPlayer(Player playerToGetPosition);
};

