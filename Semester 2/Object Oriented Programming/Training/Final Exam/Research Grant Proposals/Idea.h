#pragma once
#include <string>

class Idea
{
private:
	std::string title;
	std::string description;
	std::string status;
	std::string creator;
	int duration;
public:
	std::string filename;
	Idea() : title(""), description(""), status(""), creator(""), duration(0), filename("") {}
	Idea(std::string title, std::string description, std::string status, std::string creator, int duration, std::string filename = "")
		: title(title), description(description), status(status), creator(creator), duration(duration) 
	{
		this->filename = title + ".txt";
	}

	std::string getTitle() { return title; }
	std::string getDescription() { return description; }
	std::string getStatus() { return status; }
	std::string getCreator() { return creator; }
	int getDuration() { return duration; }
	void accept() {status = "accepted";}

	friend std::istream& operator>>(std::istream& inputStream, Idea& idea);
	std::string toString();

};

