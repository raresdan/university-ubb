#pragma once
#include <string>

class Player
{
private:
	std::string name;
	std::string nationality;
	std::string team;
	int numberOfGoals;
public:
	Player(): name(""), nationality(""), team(""), numberOfGoals(0) {}
	Player(std::string name, std::string nationality, std::string team, int numberOfGoals);

	std::string getName() const;
	std::string getNationality() const;
	std::string getTeam() const;
	int getNumberOfGoals() const;

	bool operator==(Player playerToCompare);
};

