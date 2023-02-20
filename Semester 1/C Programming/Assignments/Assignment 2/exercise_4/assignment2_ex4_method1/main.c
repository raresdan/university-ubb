
#include <stdio.h>
#include <stdlib.h>

/* Write a program that, given an integer n, computes the first n values fromFibonacci Series. */
int main()
{
    int fib1, fib2, fib3, n, count;
    fib1 = 0;
    fib2 = 1;
    count = 0;
    printf("How many terms do you want? \n");
    scanf("%d", &n);
    printf("First %d Fibonacci numbers are\n", n);
    printf("%d\n", fib1);
    printf("%d\n", fib2);
    count = 2;
    while (count < n)
    {
        fib3 = fib1 + fib2;
        count++;
        printf("%d\n", fib3);
        fib1 = fib2;
        fib2 = fib3;
   }
    return 0;
}
