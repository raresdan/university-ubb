#include "A89.h"
#include "Gui.h"
#include "Tutorial.h"
#include "Repository.h"
#include "AdministratorService.h"
#include "UserService.h"
#include "CsvWatchlist.h"
#include "HtmlWatchlist.h"
#include "Exception.h"
#include "Tests.h"
#include <iostream>
#include <crtdbg.h>
#include <vector>

#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    {
        try
        {
            Repository repository{ "Tutorials.txt" };
            FileWatchlist* filePointer = nullptr;

            AdministratorService aministratorService{ repository };
            UserService userService{ repository, filePointer };

            Gui console{ aministratorService, userService };

            Tests testing;
            testing.testAll();
            //std::cout << "All tests passed succesfully!\n\n";
            cout << endl << endl;
            console.startScreen();
        }
        catch (FileException&)
        {
            cout << "Repository file could not be opened! The application will terminate." << endl;
            return 1;
        }
    }
    _CrtDumpMemoryLeaks();
}
