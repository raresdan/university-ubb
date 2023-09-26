#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "ui.h"
#include "tests.h"

int main()
{
    setbuf(stdout, NULL);
    testAll();
    startApplication();
    return 0;
}

