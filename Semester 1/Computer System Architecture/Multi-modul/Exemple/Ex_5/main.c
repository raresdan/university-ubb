#include <stdio.h>

// Dacă utilizăm compilatorul C din Microsoft Visual Studio 2015, 2017, 2019
// este necesar să includem librăria legacy_stdio_definitions.lib la linkeditare
#pragma comment(lib, "legacy_stdio_definitions.lib")

// Această librărie este necesară doar pentru Microsoft Visual Studio 2019
// #pragma comment(lib, "legacy_stdio_wide_specifiers.lib")

// Forțăm linkeditorul să includă definiției funcției printf()
// în executabilul final, deoarece o vom apela din modulul ASM
#pragma comment(linker, "/INCLUDE:_printf")


// declaratia procedurii ASM
void afisare(int);


int main()
{
    int n = 10;
    afisare(n);     // apelul procedurii ASM
    
    return 0;
}