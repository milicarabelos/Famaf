#include <stdlib.h>
#include <stdio.h>

/* ¿Qué valor se mostraría al ejecutar la función main() del programa anterior? 
 res= 98
*/
void absolute(int x, int y) {

    if (x>0)
    {
        y= x;
    }
    else{
        y = -x;
    }
    
}

int main(void) {
    int a, res ;
    res= 0;
    a = -98;
    
    absolute(a,res);

    printf("res = %d \n",res );
    res =0;
    return EXIT_SUCCESS;
}

/* ¿Qué valor se muestra por pantalla? ¿Coincide con el programa en el lenguaje del teórico? 
se muestra el valor res = 0 porque las variables de abs solo viven en el entorno de esa funcion en cambio res
en el entorno de main solo tiene un valor = 0 */
