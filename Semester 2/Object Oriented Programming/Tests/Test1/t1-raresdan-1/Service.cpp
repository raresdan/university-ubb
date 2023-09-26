#include "Service.h"
#include <algorithm>

bool sortByGoals(Player first, Player second)
{
	if (first.getNumberOfGoals() <= second.getNumberOfGoals())
		return 1;
	return 0;
}

Service::Service(Repository initialRepository) : repository{initialRepository}
{
	this->addPlayer("Nora Mork", "NOR", "Lavrik", 83);
	this->addPlayer("Issabell", "SWE", "CSM", 3);
	this->addPlayer("Cristina", "ROU", "CSM", 4);
	this->addPlayer("Allison", "FRA", "Lavrik", 5);
	this->addPlayer("Ilina", "RUS", "HCM", 86);
	this->addPlayer("Nerea", "ESP", "Lavrik", 7);
}

std::vector<Player> Service::getAllPlayers()
{
	return this->repository.getAllPlayers();
}

bool Service::addPlayer(std::string name, std::string nationality, std::string team, int numberOfGoals)
{
	Player playerToAdd{ name, nationality, team, numberOfGoals };
	return this->repository.addPlayer(playerToAdd);
}

std::vector<Player> Service::getAllTeam(std::string  teamToGetPlayers)
{
	std::vector<Player> allPlayers = this->getAllPlayers();
	std::vector<Player> allPlayersOfATeam = {};
	int totalGoals = 0;
	for (const auto& player : allPlayers)
	{
		if (player.getTeam() == teamToGetPlayers)
			allPlayersOfATeam.push_back(player);
	}
	std::sort(allPlayersOfATeam.begin(), allPlayersOfATeam.end(), sortByGoals);
	return allPlayersOfATeam;
}

void Service::sortByNumberOfGoals(std::vector<Player> allPlayers)
{
	std::sort(allPlayers.begin(), allPlayers.end(), sortByGoals);
}

void Service::initialiseRepository()
{
}

int Service::calculateTotalGoalsScoredByATeam(std::string teamToCalculateTotalGoals)
{
	std::vector<Player> allPlayers = this->getAllPlayers();
	int totalGoals = 0;
	for (const auto& player : allPlayers)
	{
		if (player.getTeam() == teamToCalculateTotalGoals)
			totalGoals += player.getNumberOfGoals();
	}
	return totalGoals;
}
