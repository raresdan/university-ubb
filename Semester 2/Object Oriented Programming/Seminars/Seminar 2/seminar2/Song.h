#pragma once
#include <string>

// we are not using 'namespace std' to not have abiguous declarations (errors), 
//instead we write 'std::' before 

class Song
{
private:
	std::string artist;
	std::string title;
	int duration;

public:
	Song(const std::string& _artist, 
		 const std::string& _title, 
		 int _duration);
	std::string getTitle();
	void setTitle(const std::string& title);
};

