/*Write a program that reads 2 arrays and merges the two arrays into third array. Before merging, sorte
the 2 arrays in ascending order.*/


#include <stdio.h>
#include <stdlib.h>

void sort_array(int *array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (*(array + j) > *(array + j + 1))
            {
                int temp = *(array + j);
                *(array + j) = *(array + j + 1);
                *(array + j + 1) = temp;
            }
        }
    }
}


void merge_arrays(int *array1, int *array2, int *merged_array, int size1, int size2)
{
    int *i = array1;
    int *j = array2;
    int *k = merged_array;
    while (i < array1 + size1 && j < array2 + size2)
    {
        if (*i < *j)
        {
            *k = *i;
            i++;
        }
        else
        {
            *k = *j;
            j++;
        }
        k++;
    }
    while (i < array1 + size1)
    {
        *k = *i;
        i++;
        k++;
    }
    while (j < array2 + size2)
    {
        *k = *j;
        j++;
        k++;
    }
}

int main(void)
{
    int array1[100] ={}, n;
    int array2[100] ={}, m;
    int merged_array[200] ={};

    printf("Enter the length for array1: ");
    scanf("%d", &n);
    printf("Enter the values for array1: \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array1[i]);
    }

    printf("Enter the length for array2: ");
    scanf("%d", &m);
    printf("Enter the values for array2: \n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &array2[i]);
    }

    sort_array(array1, n);
    sort_array(array2, m);

    merge_arrays(array1, array2, merged_array, n, m);

    for (int i = 0; i < n+m; i++)
    {
        printf("%d ", merged_array[i]);
    }
    printf("\n");

    return 0;
}



