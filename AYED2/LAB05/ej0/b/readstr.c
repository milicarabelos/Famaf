#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void) {
    char user_input[MAX_LENGTH];

    printf("Ingrese su nombre y apellido: ");
/*  scanf("%s", user_input); 
    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);*/
    fgets(user_input,MAX_LENGTH,stdin);
    //printf("a ver %lu ", strlen(user_input));
    user_input[strlen(user_input)-1] = '\0';
    //strtok(user_input,"\n");
    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);
    return EXIT_SUCCESS;
}

