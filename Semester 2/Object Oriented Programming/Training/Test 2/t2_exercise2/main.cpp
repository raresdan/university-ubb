#include <iostream>
#include "Ui.h"

int main()
{
    Person person{ "Danny" };
    Ui console{ person };
    console.startApplication();
}
