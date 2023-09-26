#include <iostream>
#include <crtdbg.h>
#include "Ui.h"

int main()
{
    std::vector<Bill> allBills;
    Repository repository{ allBills };
    Service service{ repository };
    service.initializeRepository();
    Ui console{ service };
    console.startApplication();
}


