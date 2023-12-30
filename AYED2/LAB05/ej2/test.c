#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"

int main()
{   
    stack_elem elem;
    unsigned int amount, lenght;
    stack s = stack_empty();

    printf("cuantos elementos va a tener su stack\n");
    scanf("%u", &amount);
    

    for (unsigned int i = 0; i < amount; i++)
    {
        printf("ingrese un elemento\n");
        scanf("%d", &elem);
        s = stack_push(s,elem);
        printf("capacity is %u\n", stack_capacity(s));


    }

/*     s=stack_pop(s); 
    lenght = stack_size(s);
    printf("la longitud es %u \n", lenght); 
 */
    s = stack_push(s,13);
    s = stack_push(s,14);       
    s = stack_push(s,15);

    s = stack_push(s,13);
    s = stack_push(s,14);       
    s = stack_push(s,15); 

    s = stack_push(s,13);
    s = stack_push(s,14);     
    s = stack_push(s,15); 

    lenght = stack_size(s);
    printf("la longitud es %u \n", lenght);
    int e= stack_top(s);
    printf("el ultimo elemento es %d", e);



    stack_elem *a;
    a = stack_to_array(s);

    for (unsigned int i = 0; i <= lenght; i++)
    {
    printf ("a en %u es  %d \n\n",i , a[i]);

    }

    free(a);
    stack_destroy(s);
    printf("fin del programa\n");

    return 0;
}
