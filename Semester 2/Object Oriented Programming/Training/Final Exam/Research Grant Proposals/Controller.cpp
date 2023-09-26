#include "Controller.h"
#include <fstream>

void Controller::addIdea(Idea& idea)
{
	if (idea.getDuration() > 4 || idea.getDuration() < 0)
		throw std::exception("Invalid duration!");
	if(idea.getTitle() == "" || idea.getDescription() == "")
		throw std::exception("Invalid title or description!");
	this->ideas.push_back(idea);
}

void Controller::acceptIdea(int indexOfIdea)
{
	if(indexOfIdea < 0 || indexOfIdea >= ideas.size())
		throw std::exception("Invalid index!");
	if(ideas[indexOfIdea].getStatus() == "accepted")
		throw std::exception("Idea already accepted!");
	ideas[indexOfIdea].accept();
}

void Controller::readIdeas()
{
	std::ifstream inputFile{ "ideas.txt" };
	Idea idea;
	while(inputFile >> idea)
		ideas.push_back(idea);
	inputFile.close();
}

void Controller::readResearchers()
{
	std::ifstream inputFile{ "researchers.txt" };
	Researcher researcher;
	while(inputFile >> researcher)
		researchers.push_back(researcher);
	inputFile.close();
}

void Controller::writeIdeas()
{
	std::ofstream outputFile{ "ideas.txt" };
	if(!outputFile.is_open())
		throw std::exception("File could not be opened!");
	for(auto idea : ideas)
		outputFile << idea.toString() << std::endl;
	outputFile.close();
}
