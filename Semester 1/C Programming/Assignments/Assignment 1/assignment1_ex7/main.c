/* Being given the values of the diagonals of a diamond shape (romb), compute the
area and perimeter of the diamond shape.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int d1=0,d2=0,side=0,area=0,perimeter=0;
    printf("Give the length of the first diagonal of a diamond shape: ");
    scanf("%d", &d1);
    printf("Give the length of the second diagonal of a diamond shape: ");
    scanf("%d", &d2);
    side = sqrt(d1/2*d1/2 + d2/2*d2/2);
    area = (d1*d2)/2;
    perimeter= 4*side;
    printf("A diamond shape with the diagonals %d and %d will have the area %d and the perimeter %d", d1,d2,area,perimeter);
    return 0;
}
