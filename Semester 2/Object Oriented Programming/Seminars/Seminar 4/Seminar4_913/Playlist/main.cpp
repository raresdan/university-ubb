#include "UI.h"
#include <Windows.h>
#include "RepositoryExceptions.h"
#include "CsvPlaylist.h"
#include "JSONPlayList.h"

using namespace std;

//class A
//{
//public:
//	virtual int f() {
//		return 1;
//	}
//	virtual ~A() {
//		cout << "Destructor in A" << endl;
//	}
//};
//
//class B : public A
//{
//private:
//	int* x;
//
//public:
//	B()	{
//		x = new int{ 20 };
//	}
//	~B() {
//		delete x;
//		cout << "Destructor in B" << endl;
//	}
//	int f()
//	{
//		return 2;
//	}
//};


int main()
{
	/*A* obj = new B{};
	cout << obj->f();
	delete obj;*/


	system("color f4");

	try
	{
		Repository repo("Songs.txt");
		FilePlaylist* p = nullptr;
		cout << "What type of file would you like to use to store the playlist (CSV/JSON)?";
		string fileType{};
		cin >> fileType;
		if (fileType == "CSV")
			p = new CsvPlaylist{ "playlist.csv" };
		else
			p = new JSONPlayList{ "playlist.json" };
		Service ctrl(repo, p);
		UI ui(ctrl);
		ui.run();
		delete p;
	}
	catch (FileException&)
	{
		cout << "Repository file could not be opened! The application will terminate." << endl;
		return 1;
	}

	return 0;
}