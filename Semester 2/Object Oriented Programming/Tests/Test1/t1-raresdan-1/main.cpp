#include <iostream>
#include "Ui.h"
#include "Tests.h"


int main()
{
    {
        std::vector<Player> initialPlayers = {};
        Repository repository{ initialPlayers };
        Service service{ repository };
        service.initialiseRepository();
        Ui console{ service };

        Tests testing;
        testing.testAll();
        std::cout << "Passed!\n\n";

        console.startApplication();
    }
}

