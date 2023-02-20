/*Knowing that we have coins of 1, 2 and 5 units, determine the minimum number of
coins to pay a given amount.*/

#include <stdio.h>
#include <stdlib.h>
#define coin1 1
#define coin2 2
#define coin5 5

int main()
{
    int value=0,copy;
    int count5=0, count2=0, count1=0;
    printf("Enter the amount you want to pay: ");
    scanf("%d", &value);
    copy = value;
    while(value >= coin5)
        {
            count5 ++;
            value = value - coin5;
        }

    while(value >= coin2)
        {
            count2 ++;
            value = value - coin2;
        }
    while(value >= coin2)
        {
            count1 ++;
            value = value - coin1;
        }

    printf("To pay %d there were used: %d coins of 5, %d coins of 2, %d coins of 1", copy, count5, count2, count1);
    return 0;
}
