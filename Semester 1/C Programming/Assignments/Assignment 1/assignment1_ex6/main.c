/*Given the natural number h and m, that represent the current time expressed in
hours and minutes, compute the time after x hours and y minutes.*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int h,m, x, y, cx, cy;
    do{
        printf("Give the current hour: ");
        scanf("%d", &h);
        }
    while(h > 24 || h < 0);
    do{
        printf("Give the current minutes: ");
        scanf("%d", &m);
        }
    while(m > 60 || m < 0);
    x = cx =  5;
    y = cy = 450;
    while(y >= 60)
    {
        h ++;
        y -= 60;
    }
    m += y;
    h += x;
    if (m>60)
    {
        h ++;
        m = m - 60;
    }
    printf("After %d hours and %d minutes the time will be: %d:%d",cx, cy, h%24, m);
    return 0;
}
