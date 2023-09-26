#include "Player.h"

Player::Player(std::string name, std::string nationality, std::string team, int numberOfGoals)
{
	this->name = name;
	this->nationality = nationality;
	this->team = team;
	this->numberOfGoals = numberOfGoals;
}

std::string Player::getName() const
{
	return this->name;
}

std::string Player::getNationality() const
{
	return this->nationality;
}

std::string Player::getTeam() const
{
	return this->team;
}

int Player::getNumberOfGoals() const
{
	return this->numberOfGoals;
}

bool Player::operator==(Player playerToCompare)
{
	if (this->name == playerToCompare.getName())
		return true;
	return false;
}
