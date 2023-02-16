#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 //preguntar valgrind 
struct _s_stack
 {
     stack_elem elem;
     struct _s_stack *next;

 };

stack stack_empty(){
     return NULL;
 }

stack stack_push(stack s, stack_elem e){
    stack p = malloc(sizeof(struct _s_stack));
    p->elem = e;
    p->next = s;
    s = p;
    p=NULL;
    return s;
}

stack stack_pop(stack s){

    assert(!stack_is_empty(s));
    stack p = s;
    s = s->next;
    free(p); //este free es invalido 
    p = NULL;

    return s;
}

unsigned int stack_size(stack s){
    
    int n = 0;
    stack p = s;
    while (p != NULL)
    {
        n = n + 1;
        p = p->next;
    }
    
    return n;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    stack_elem e=s->elem;
    return e;
}

bool stack_is_empty(stack s){
    return (s == NULL);
}
/* 
stack_elem *stack_to_array(stack s){

    int lenght = stack_size(s); //calculo la longitud del arreglo
    stack_elem *a=NULL;                //declaro el arreglo
    //stack copy = stack_copy(s);
    
    a = calloc(lenght, sizeof(stack_elem) );

    for( int i = lenght-1 ; i >=0 ; --i)
    {
        a[i] = stack_top(s);
        s = stack_pop(s);
    }

    for (int i = lenght-1; i >= 0; --i)
    {
        s = stack_push(s,a[i]);
    }
    
    //copy = stack_destroy(copy);

    return a;
} */

stack_elem *stack_to_array(stack s){
    stack p=s;
    int lenght = stack_size(s);
    stack_elem *a = calloc(lenght, sizeof(stack_elem));

    for (int i = lenght -1 ; i >= 0; i--)
    {
        a[i] = p->elem;
        p = p->next;
    }

    p = NULL;
    return a;
}

stack stack_destroy(stack s){
/*     for (unsigned int i = 0; i < stack_size(s); i--)
    {
        stack_pop(s);
    } */
    stack p = s;

    while (p != NULL)
    {
        p = p->next;
        free(s);
        s = p;
    }
    
    return NULL;
}

/* stack stack_copy(stack s){
    
    stack p;
    unsigned int n=0;
    unsigned int lenght = stack_size(s);
    stack_elem e;
    p = stack_empty();
    stack q;
    q = s;

    while (n < lenght)
    {
        e = q->elem;
        q = s->next;
        n++;
        p = stack_push(p,e); 
    }
    
    return p;
} */

