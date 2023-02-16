#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "array_helpers.h"


#define MAX_SIZE 1000

char *parse_filepath(int argc, char *argv[])
{
    // Parse the filepath given by command line argument.
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count)
    {
        printf("cantidad invalida de argumentos");
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size)
{
    FILE *file;
    unsigned int i = 0;
    file = fopen(path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    while (!feof(file))
    {
        (fscanf(file, "%u '%c'\n", &(indexes[i]), &(letters[i])));

        /*         fscanf(file, "%u %c\n", &(indexes[i]) , &(letters[i])); */

        if (i > max_size)
        {
            printf("el arreglo es demasiado grande");
            exit(EXIT_FAILURE);
        }

        i++;
    }

    fclose(file);

    return i;
}

int main(int argc, char *argv[])
{
    char *file;
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length = 0;
    //  .----------^
    //  :
    // Debe guardarse aqui la cantidad de elementos leidos del archivo

    /*  -- completar -- */

    // creo el puntero que apunta al archivo y se lo asigno a file
    file = parse_filepath(argc, argv);
    // leo los elementos del archivo y completo los arreglos, tambien consigo el valor de lenght
    length = data_from_file(file, indexes, letters, MAX_SIZE);
/*     //este es el arreglo de numeros
    array_dump(indexes, length);
    //este es el arreglo de letras
    dump(letters, length); */
    //ordeno el arreglo de letras en funcion a sus indices
    array_sorted(indexes, letters, sorted, length);
    // imprimo el arreglo ordenado
    dump(sorted, length);
    return EXIT_SUCCESS;
}
