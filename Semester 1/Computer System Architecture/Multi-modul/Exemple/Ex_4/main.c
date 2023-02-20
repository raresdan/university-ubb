#include <stdio.h>

// declararea procedurii ASM
void afisare(int);


int main()
{
    int n = 10;
    
    // Dacă nu utilizâm funcția printf() în main(),
    // linkeditorul nu va include definiția acestei funcții
    // în executabilul final.
    
    // Comentarea liniei 18 va produce eroare la linkeditare:
    // modul.obj : error LNK2001: unresolved external symbol _printf
    // main.exe : fatal error LNK1120: 1 unresolved externals
    // printf("Cifrele de la 0 la %d:\n", n);
    
    afisare(n);     // apelul procedurii ASM
    
    return 0;
}