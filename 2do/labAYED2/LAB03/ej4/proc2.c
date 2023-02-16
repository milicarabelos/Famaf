#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

void absolute(int x, int *y) {
    // Completar aqui
    if (x>0)
    {
        *y = x;
    }
    else{
        *y = -x;
    }
}

int main(void) {
    int a;
    int *res;

    res  = malloc (sizeof(int));
    *res = 0;  
    a = -98;
    
    absolute(a,res);

    printf("res = %d \n",*res );
    *res =0;
    return EXIT_SUCCESS;
}

/* ¿Se muestra el valor correcto?
ahora si conseguimos el valor correcto porque al ser res un puntero apuntamos al espacio de memoria y
la variable que se aloje en ese espacio de memoria es global es decir afecta para todas nuestras funciones 

el parametro res es de tipo out en res porque solo lo escribimos nunca leemos cuanto vale*/