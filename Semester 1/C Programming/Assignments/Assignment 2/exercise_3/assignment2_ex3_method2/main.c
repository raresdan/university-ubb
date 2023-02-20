#include <stdio.h>
#include <stdlib.h>

void spelling(int n)
{
    int first_digit = n/100;
    int second_digit = n/10%10;
    int last_digit = n%10;
    switch(first_digit)
    {
        case 1:
            printf("one hundred ");
            break;
        case 2:
            printf("two hundred ");
            break;
        case 3:
            printf("three hundred ");
            break;
        case 4:
            printf("four hundred ");
            break;
        case 5:
            printf("five hundred ");
            break;
        case 6:
            printf("six hundred ");
            break;
        case 7:
            printf("seven hundred ");
            break;
        case 8:
            printf("eight hundred ");
            break;
        case 9:
            printf("nine hundred ");
            break;
        default:
            printf(" ");
    }
    switch(second_digit)
    {
        case 2:
            printf("twenty ");
            break;
        case 3:
            printf("thirty ");
            break;
        case 4:
            printf("fourty ");
            break;
        case 5:
            printf("fifty ");
            break;
        case 6:
            printf("sixty ");
            break;
        case 7:
            printf("seventy ");
            break;
        case 8:
            printf("eighty ");
            break;
        case 9:
            printf("ninty ");
            break;
        default:
            printf(" ");
    }
    if(second_digit == 1)
        switch(first_digit)
    {
        case 1:
            printf("eleven");
            break;
        case 2:
            printf("twelve");
            break;
        case 3:
            printf("thirteen");
            break;
        case 4:
            printf("fourteen");
            break;
        case 5:
            printf("fifteen");
            break;
        case 6:
            printf("sixteen");
            break;
        case 7:
            printf("seventeen");
            break;
        case 8:
            printf("eighteen");
            break;
        case 9:
            printf("nineteen");
            break;
        default:
            printf(" ");
    }
    else
        switch(first_digit)
        {
            case 1:
                printf("one");
                break;
            case 2:
                printf("two");
                break;
            case 3:
                printf("three");
                break;
            case 4:
                printf("four");
                break;
            case 5:
                printf("five");
                break;
            case 6:
                printf("six");
                break;
            case 7:
                printf("seven");
                break;
            case 8:
                printf("eight");
                break;
            case 9:
                printf("nine");
                break;
            default:
                printf(" ");
        }
}
int main()
{
    int n;
    do{
        printf("Enter a 3-digit integer: ");
        scanf("%d", &n);
    }while(n<0 || n > 999);
    spelling(n);
    return 0;
}
