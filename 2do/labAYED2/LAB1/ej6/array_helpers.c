#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mybool.h"
#include "array_helpers.h"

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath)
{
    // your code here!!!
    unsigned int lenght;
    max_size = max_size;
    unsigned int i = 0;
    int num;
    FILE *f;
    f = fopen(filepath, "r");

    fscanf(f, "%u", &lenght);

    if (lenght > max_size)
    {
        printf("El array es demasiado grande");
        exit(EXIT_FAILURE);
    }

    while (fscanf(f, "%d", &num) != EOF && i < lenght)
    {
        array[i] = num;
        ++i;
    }

    fclose(f);
    return lenght;
}

void array_dump(int a[], unsigned int length)
{
    // your code here!!!!!
    unsigned int i = 0;

    printf("[");
    while (i < length)
    {
        if (i == length - 1)
        {
            printf(" %d]\n", a[i]);
        }
        else
        {
            printf(" %d,", a[i]);
        }
        ++i;
    }
}

mybool array_is_sorted(int a[], unsigned int length)
{
    unsigned int i = 0;
    mybool ord = true;
    while (i < length - 1 && ord==true)
    {
     ord = a[i]<a[i+1];
     i++;
    }
return ord;
}

void array_swap(int a[], unsigned int i, unsigned int j)
{ int aux;
  aux = a[i];
  a[i] = a[j];
  a[j] = aux;
}