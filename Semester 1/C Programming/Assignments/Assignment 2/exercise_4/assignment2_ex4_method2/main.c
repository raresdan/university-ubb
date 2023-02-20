
#include <stdio.h>
#include <stdlib.h>

void fibonacci(int n)
{
    int fib1, fib2, fib3, count;
    fib1 = 0;
    fib2 = 1;
    count = 0;
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
}
int main()
{
    int n;
    printf("How many terms do you want? \n");
    scanf("%d", &n);
    fibonacci(n);
    return 0;
}
