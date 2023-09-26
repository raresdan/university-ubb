#include "UI.h"
#include <string>

using namespace std;

void UI::printMenu()
{
	cout << endl;
	cout << "1 - Manage song repository."<<endl;
	cout << "2 - Manage playlist." << endl;
	cout << "0 - Exit." << endl;
}

void UI::printRepositoryMenu()
{
	cout << "Possible commands: " << endl;
	cout << "\t 1 - Add song." << endl;
	cout << "\t 2 - Display all." << endl;
	cout << "\t 0 - Back." << endl;
}

void UI::printPlayListMenu()
{
	cout << "Possible commands: " << endl;
	cout << "\t 1 - Add song." << endl;
	cout << "\t 2 - Add songs by artist." << endl;
	cout << "\t 3 - Play." << endl;
	cout << "\t 4 - Next." << endl;
	cout << "\t 0 - Back." << endl;
}

void UI::addSongToRepo()
{
	cout << "Enter the artist: ";
	std::string artist;
	getline(cin, artist);
	cout << "Enter the title: ";
	std::string title;
	getline(cin, title);
	double minutes = 0, seconds = 0;
	cout << "Enter the duration: " << endl;
	cout << "\tMinutes: ";
	cin >> minutes;
	cin.ignore();
	cout << "\tSeconds: ";
	cin >> seconds;
	cin.ignore();
	cout << "Youtube link: ";
	std::string link;
	getline(cin, link);
	
	this->service.addSongToRepository(artist, title, minutes, seconds, link);
}

void UI::displayAllSongsRepo()
{
	DynamicVector songs = this->service.getAllSongsInRepo();
	for (int i = 0; i < songs.getSize(); i++)
	{
		Song s = songs.get(i);
		cout << s.toString() << endl;
	}
}

void UI::addSongToPlaylist()
{
	// TODO
}

void UI::addAllSongsByArtistToPlaylist()
{
	cout << "Enter the artist: ";
	std::string artist;
	getline(cin, artist);

	this->service.addAllSongsByArtistToPlaylist(artist);
}

void UI::run()
{
	while (true)
	{
		UI::printMenu();
		int command{ 0 };
		cout << "Input the command: ";
		cin >> command;
		cin.ignore();
		if (command == 0)
			break;

		// repository management
		if (command == 1)
		{
			while (true)
			{
				UI::printRepositoryMenu();
				int commandRepo{0};
				cout << "Input the command: ";
				cin >> commandRepo;
				cin.ignore();
				if (commandRepo == 0)
					break;
				switch (commandRepo)
				{
				case 1:
					this->addSongToRepo();
					break;
				case 2:
					this->displayAllSongsRepo();
				}
			}			
		}

		// playlist management
		if (command == 2)
		{
			// TODO
		}
	}
}