#pragma once
#include "Idea.h"
#include "Researcher.h"
#include <vector>

class Controller
{
private:
	std::vector<Idea> ideas;
	std::vector<Researcher> researchers;
public:
	Controller() : ideas(), researchers() 
	{
		readIdeas();
		readResearchers();
	}

	std::vector<Idea> getIdeas() { return ideas; }
	std::vector<Researcher> getResearchers() { return researchers; }

	void addIdea(Idea& idea);
	void acceptIdea(int indexOfIdea);

	void readIdeas();
	void readResearchers();

	void writeIdeas();
};

