#include <stdlib.h>
#include <assert.h>
#include "stack.h"


//inv de representacion: size <= capacity 
unsigned int capacity=10;
struct _s_stack
{
    stack_elem *elems;     // Arreglo de elementos
    unsigned int size;     // Cantidad de elementos en la pila
    unsigned int capacity; // Capacidad actual del arreglo elems
};

stack stack_empty()
{
    stack s = malloc(sizeof(struct _s_stack));
    s->capacity = capacity;
    s->elems = calloc(capacity,sizeof(stack_elem));
    s->size = 0;
    return s;
}

stack stack_push(stack s, stack_elem e){

        if (s->size == s->capacity)
        {
            unsigned int tam = s->capacity;
            s->elems = realloc(s->elems,sizeof(stack_elem)*(tam*2));
            s->capacity = s->capacity * 2;
        }

        s->elems[s->size] = e;
        s->size = s->size + 1;

    return s;
}

stack stack_pop(stack s)
{   
    assert(!stack_is_empty(s));
    s->size = s->size - 1;
    return s;
}

unsigned int stack_size(stack s)
{
    return s->size;
}

unsigned int stack_capacity(stack s)
{
    return s->capacity;
}

stack_elem stack_top(stack s)
{  
    assert(!stack_is_empty(s));
    return s->elems[s->size-1]; //sacar el -1 
}

bool stack_is_empty(stack s)
{
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s)
{

    stack_elem *a = calloc(s->size, sizeof(struct _s_stack)); //s.size  
    for (unsigned int i = 0; i <= s->size; i++)
    {
        a[i] = s->elems[i];
    }

    return a;
}

stack stack_destroy(stack s)
{   
    free(s->elems);
    free(s);

    return NULL;

}
