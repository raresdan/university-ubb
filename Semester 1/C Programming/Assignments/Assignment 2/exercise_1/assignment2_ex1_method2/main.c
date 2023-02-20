#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maximum(int v[], int size)
{
    int maxi = 0;
    int i;
    for(i=0;i<size;i++)
    {
        if(v[i]>=maxi)
        {
            maxi = v[i];
        }
    }
    return maxi;
}
int minimum(int v[], int size)
{
    int mini = INT_MAX;
    int i;
    for(i=0;i<size;i++)
    {
        if(v[i]<=mini)
        {
            mini = v[i];
        }
    }
    return mini;
}

int main()
{
    int len=0,i,v[100];
    int minimum_value, maximum_value;
    printf("How many integers you want to read? ");
    scanf("%d",&len);
    for(i=0;i<len;i++)
        scanf("%d",&v[i]);
    minimum_value = minimum(v,len);
    maximum_value = maximum(v,len);
    printf("The minimum of the array is %d and the maximum is %d", minimum_value, maximum_value);
    return 0;
}
