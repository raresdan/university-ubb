#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declare the concatenate function
extern void concatenate(char* result, char* a, char* b, char* c, int la, int lb, int lc);

int main()
{
    char a[100], b[100], c[100], result[300] = "";
    int la, lb, lc;

    // Read the first string
    scanf("%s", a);
    // Compute the length of the first string
    la = strlen(a);
    // Read the second string
    scanf("%s", b);

    // Compute the length of the second string
    lb = strlen(b);

    // Read the third string
    scanf("%s", c);

    // Compute the length of the third string
    lc = strlen(c);

    // Concatenate the strings
    concatenate(result, a, b, c, la, lb, lc);
    
    // Print the result
    printf("%s\n", result);

    return 0;
}