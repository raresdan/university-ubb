#include "Repository.h"

Repository::Repository(std::vector<Player> initialPlayers)
{
	this->allPlayers = initialPlayers;
}

std::vector<Player> Repository::getAllPlayers()
{
	return this->allPlayers;
}

bool Repository::addPlayer(Player playerToAdd)
{
	auto iterator = std::find(this->allPlayers.begin(), this->allPlayers.end(), playerToAdd);
	if (iterator != this->allPlayers.end())
		return false;
	this->allPlayers.push_back(playerToAdd);
	return true;
}

int Repository::getPositionOfPlayer(Player playerToGetPosition)
{
	auto iterator = std::find(this->allPlayers.begin(), this->allPlayers.end(), playerToGetPosition);
	if (iterator == this->allPlayers.end())
		return -1;
	return std::distance(this->allPlayers.begin(), iterator);
}
