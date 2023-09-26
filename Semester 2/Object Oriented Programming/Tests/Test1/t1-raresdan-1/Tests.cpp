#include "Tests.h"
#include <assert.h>

void Tests::testAddRepository()
{
	std::vector<Player> initialPlayers = {};
	Repository repository{ initialPlayers };
	Player validPlayer{ "", "", "", 0 };
	assert(repository.getAllPlayers().size() == 0);
	repository.addPlayer(validPlayer);
	assert(repository.getAllPlayers().size() == 1);
}

void Tests::testAddService()
{
	std::vector<Player> initialPlayers = {};
	Repository repository{ initialPlayers };
	Service service{ repository };
}

void Tests::testGetAllTeam()
{
}

void Tests::testAll()
{
	this->testAddRepository();
	this->testAddService();
	this->testGetAllTeam();
}
