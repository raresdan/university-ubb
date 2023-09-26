#include "Tutorial.h"
#include "Utils.h"
#include <iostream>
#include <vector>

Tutorial::Tutorial(std::string title, std::string presenter, Duration duration, int likes, std::string link)
{
    this->title = title;
    this->presenter = presenter;
    this->duration = duration;
    this->likes = likes;
    this->link = link;

}

std::string Tutorial::getTitle() const
{
    return this->title;
}

std::string Tutorial::getPresenter() const
{
    return this->presenter;
}

Duration Tutorial::getDuration() const
{
    return this->duration;
}

int Tutorial::getLikes() const
{
    return this->likes;
}

std::string Tutorial::getLink() const
{
    return this->link;
}

void Tutorial::setTitle(std::string newTitle)
{
    this->title = newTitle;
}

void Tutorial::setPresenter(std::string newPresenter)
{
    this->presenter = newPresenter;
}

void Tutorial::setDuration(Duration newDuration)
{
    this->duration = newDuration;
}

void Tutorial::setLikes(int newLikes)
{
    this->likes = newLikes;
}

void Tutorial::setLink(std::string newLink)
{
    this->link = newLink;
}

bool Tutorial::operator==(const Tutorial& tutorialToCompare)
{
    if (this->title == tutorialToCompare.title && this->presenter == tutorialToCompare.presenter)
        return true;
    return false;
}

void Tutorial::operator=(const Tutorial& tutorialToCopy)
{
    this->title = tutorialToCopy.title;
    this->presenter = tutorialToCopy.presenter;
    this->duration = tutorialToCopy.duration;
    this->likes = tutorialToCopy.likes;
    this->link = tutorialToCopy.link;
}

std::istream& operator>>(std::istream& inputFile, Tutorial& tutorialToRead)
{
    std::string lineRead;
    getline(inputFile, lineRead);
    std::vector<std::string> tokens = tokenize(lineRead, ',');
    if (tokens.size() != 5) 
        return inputFile;
    tutorialToRead.title = tokens[0];
    tutorialToRead.presenter = tokens[1];
    std::vector<std::string> durationTokens = tokenize(tokens[2], ':');
    if (durationTokens.size() != 2)
        return inputFile;
    tutorialToRead.duration = Duration{ std::stoi(durationTokens[0]), std::stoi(durationTokens[1]) };
    tutorialToRead.likes = std::stoi(tokens[3]);
    tutorialToRead.link = tokens[4];
    return inputFile;
}

std::ostream& operator<<(std::ostream& outputFile, const Tutorial& tutorialToWrite)
{
    outputFile << tutorialToWrite.title << "," << tutorialToWrite.presenter << "," << tutorialToWrite.duration.minutes << ":" << tutorialToWrite.duration.seconds << "," << tutorialToWrite.likes << "," << tutorialToWrite.link << "\n";
    return outputFile;
}
