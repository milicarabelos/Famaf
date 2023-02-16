#include <stdio.h>
#include <stdlib.h>

#include "strfuncs.h"

static size_t c_in_str(const char *str, char c)
{
    size_t counter = 0;

    for (size_t i = 0; i < string_length(str); i++)
    {
        if (str[i] == c)
        {
            counter++;
        }
    }
    return counter;
}

size_t string_length(const char *str)
{

    size_t count = 0;

    while (*str != '\0')
    {
        count = count + 1;
        str++;
    }

    return count;
}

char *string_filter(const char *str, char c)
{

    char *p = NULL;
    const size_t tam = string_length(str);
    unsigned int j = 0;

    // me faltaria algo de malloc pero no se como hacerlo
    /*char letra[tam];
   p = &letra;
   */
    p = calloc((tam + 1 - c_in_str(str, c)), sizeof(str));

    if (p == NULL)
    {
        printf("no hay memoria suficiente");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i <= tam; i++)
    {

        if (str[i] != c)
        {
            p[j] = str[i];
            j++;
        }
    }

    /*     while (*str != '\0')
        {
            if (*str != c)
            {
                *p = *str;
                p++;
            }

            str++;
        } */

    return p;
}
