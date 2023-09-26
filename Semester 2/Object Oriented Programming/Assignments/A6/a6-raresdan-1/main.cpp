#include <iostream>
#include <crtdbg.h>
#include "Ui.h"
#include "Tests.h"

int main()
{
    {
        std::vector<Tutorial> allTutorials;

        Repository repository{ allTutorials };

        AdministratorService aministratorService{ repository };
        aministratorService.initializeAllTutorials();
        UserService userService{ repository };

        Ui console{ aministratorService, userService };

        Tests testing;
        testing.testAll();
        std::cout << "All tests passed succesfully!\n\n";

        console.startApplication();
    }

     _CrtDumpMemoryLeaks();
}

