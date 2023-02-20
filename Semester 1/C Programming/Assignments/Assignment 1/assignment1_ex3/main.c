#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,v[6],maxi,mini;
    printf("Give 5 integers: \n");
    for (i=1;i<=5;i++)
    {
        scanf("%d", &v[i]);
    }
    maxi = 0;
    mini = v[1];
    for (i=1;i<=5;i++)
    {
        if (v[i] >= maxi)
            maxi = v[i];
        if (v[i] <= mini)
            mini = v[i];
    }
    printf("The maximal value is: %d\n", maxi);
    printf("The minimal value is: %d\n", mini);
    return 0;
}
