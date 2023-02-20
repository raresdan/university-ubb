#include <stdio.h>
#include <stdlib.h>

/* Read two integers and compute their sum, average and sum of the squares of the numbers. */

int main()
{
    int a,b;
    int sum, average, squares_sum;
    printf("The value of the first integer:\n");
    scanf("%d", &a);
    printf("The value of the second integer:\n");
    scanf("%d", &b);
    sum = a + b;
    printf("The sum of the two integers is: %d\n", sum);
    average = (a + b)/2;
    printf("The average of the two integers is: %d\n", average);
    squares_sum = a*a + b*b;
    printf("The sum of the squares of the two integers is: %d\n", squares_sum);
    return 0;
}
