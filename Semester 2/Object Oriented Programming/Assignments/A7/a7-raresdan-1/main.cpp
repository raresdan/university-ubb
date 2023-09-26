#include <iostream>
#include <crtdbg.h>
#include "Ui.h"
#include "Tests.h"
#include "CsvWatchlist.h"
#include "HtmlWatchlist.h"
#include "Exception.h"

using namespace std;

int main()
{
    {
        try
        {
            Repository repository{ "Tutorials.txt" };
            FileWatchlist* filePointer = nullptr;
            cout << "What type of file would you like to use to store the playlist (CSV/HTML)?\n";
            string fileType{};
            cin >> fileType;
            if (fileType == "CSV")
                filePointer = new CsvWatchlist{ "watchlist.csv" };
            else
                filePointer = new HtmlWatchlist{ "watchlist.html" };

            AdministratorService aministratorService{ repository };
            UserService userService{ repository, filePointer };

            Ui console{ aministratorService, userService };

            //Tests testing;
            //testing.testAll();
            //std::cout << "All tests passed succesfully!\n\n";
            cout << endl << endl;
            console.startApplication();
        }
        catch (FileException&)
        {
            cout << "Repository file could not be opened! The application will terminate." << endl;
            return 1;
        }
    }
     _CrtDumpMemoryLeaks();
}

