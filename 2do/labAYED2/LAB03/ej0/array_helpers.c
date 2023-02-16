#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void dump(char a[], unsigned int length)
{
    printf("\"");
    for (unsigned int j = 0u; j < length; j++)
    {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

void array_dump(unsigned int a[], unsigned int length)
{
    // your code here!!!!!
    unsigned int i = 0;

    printf("[");
    while (i < length)
    {
        if (i == length - 1)
        {
            printf(" %u]\n", a[i]);
        }
        else
        {
            printf(" %u,", a[i]);
        }
        ++i;
    }
}

void array_sorted(unsigned int indexes[], char letters[], char sorted[], unsigned int lenght)
{
    unsigned int i, num;
    i = 0;

    while (i < lenght)
    {
        num = indexes[i];
        sorted[num] = letters[i];

        if (indexes[i] > lenght)
        {
            printf("el formato no es correcto \n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}