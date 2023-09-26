#include "Ui.h"
#include <iostream>

#define EXIT 0
#define ADD_PLAYER 1
#define SHOW_PLAYERS 2
#define SHOW_TEAM 3

Ui::Ui(Service initialService): service{initialService}
{
}

void Ui::addPlayer()
{
	std::string name, nationality, team;
	int numberOfGoals = 0;
	std::cout << "Name: ";
	std::cin.ignore();
	getline(std::cin, name);
	std::cout << "Nationality: ";
	getline(std::cin, nationality);
	std::cout << "Team: ";
	getline(std::cin, team);
	std::cout << "Goals: ";
	std::cin >> numberOfGoals;

	bool checkAdded = this->service.addPlayer(name, nationality, team, numberOfGoals);
	if (checkAdded == false)
		std::cout << "Player already exists!";
	else
		std::cout << "Player added successfully";
}

void Ui::displayAllPlayers()
{
	std::vector<Player> allPlayers = this->service.getAllPlayers();
	for (const auto& player : allPlayers)
	{
		std::cout << "Name: " << player.getName() << std::endl;
		std::cout << "Nationality: " << player.getNationality () << std::endl;
		std::cout << "Team: " << player.getTeam() << std::endl;
		std::cout << "Goals: " << player.getNumberOfGoals() << std::endl;
		std::cout << std::endl;
	}

}

void Ui::displayAllPlayersOfTeam()
{
	std::string team;
	std::cout << "Team: ";
	std::cin.ignore();
	getline(std::cin, team);

	std::vector<Player> allPlayersOfATeam = this->service.getAllTeam(team);
	this->service.sortByNumberOfGoals(allPlayersOfATeam);
	for (const auto& player : allPlayersOfATeam)
	{
		std::cout << "Name: " << player.getName() << std::endl;
		std::cout << "Nationality: " << player.getNationality() << std::endl;
		std::cout << "Team: " << player.getTeam() << std::endl;
		std::cout << "Goals: " << player.getNumberOfGoals() << std::endl;
		std::cout << std::endl;
	}
	std::cout << "Total Goals: " << this->service.calculateTotalGoalsScoredByATeam(team);
}

void Ui::printMenu()
{
	std::cout << "Menu\n\n";
	std::cout << "1. Add Player\n";
	std::cout << "2. Show all Players\n";
	std::cout << "3. Show Players of a team\n";
	std::cout << "0. EXIT\n";
}

void Ui::startApplication()
{
	int optionChosen;
	printMenu();
	while (true)
	{
		std::cout << "\nEnter your option: ";
		std::cin >> optionChosen;
		if (std::cin.fail() || optionChosen < 0 || optionChosen > 3) {
			std::cout << "\nInvalid input! Please enter a valid option.\n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		switch (optionChosen)
		{
		case ADD_PLAYER:
			this->addPlayer();
			break;
		case SHOW_PLAYERS:
			this->displayAllPlayers();
			break;
		case SHOW_TEAM:
			this->displayAllPlayersOfTeam();
			break;
		case EXIT:
			std::cout << std::endl;
			return;
		default:
			std::cout << "\nInvalid option! Please try again!\n\n";
			break;
		}
	}
}
