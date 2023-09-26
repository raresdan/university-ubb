#include <iostream>
#include "Ui.h"
#include "Tests.h"
#include <crtdbg.h>

int main()
{
    {
        std::vector<Car> initialCars = {};
        Repository repository{ initialCars };
        Service service{ repository };
        service.initializeRepository();
        Ui console{ service };

        Tests testing;
        testing.testAll();
        std::cout << "All tests passed!\n\n";

        console.startApplication();
    }
    _CrtDumpMemoryLeaks();
}

