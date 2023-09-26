#pragma once
#include "Repository.h"

class Service
{
private:
	Repository repository;
public:
	Service(Repository initialRepositor);
	std::vector<Player> getAllPlayers();
	std::vector<Player> getAllTeam(std::string teamToGetPlayers);
	bool addPlayer(std::string name, std::string nationality, std::string team, int numberOfGoals);
	void sortByNumberOfGoals(std::vector<Player> allPlayers);
	int calculateTotalGoalsScoredByATeam(std::string teamToCalculateTotalGoals);
	void initialiseRepository();
};

