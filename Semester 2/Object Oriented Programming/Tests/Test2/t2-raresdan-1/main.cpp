
#include <iostream>
#include "Ui.h"

int main()
{
    Controller controller;
    Ui console{ controller };
    console.startApplication();
}

