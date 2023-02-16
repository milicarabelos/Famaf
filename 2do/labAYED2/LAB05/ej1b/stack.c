#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack
 {
     stack_elem elem;
     struct _s_stack *next;
     int cant;

 };

stack stack_empty(){
     return NULL;
 }

stack stack_push(stack s, stack_elem e){
    stack p = NULL;
    p = malloc(sizeof(struct _s_stack));
    p->elem = e;
    p->next = s;
    
    if (stack_is_empty(s))
    {
        p->cant = 1;
    }
    else{
        p->cant= s->cant + 1;
    }

    s = p;
    p=NULL;
    return s;
}

stack stack_pop(stack s){

    assert(!stack_is_empty(s));
    struct _s_stack *p = NULL;
    p = s;
    s = s->next;
    free(p);
    p = NULL;

    return s;
}

unsigned int stack_size(stack s)
{
    unsigned int cant;
    if (s == NULL)
    {
        cant = (unsigned int)0;
    }
    else{
    cant = (unsigned int)s->cant;
    }
    return cant;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    stack_elem e=s->elem;
    return e;
}

bool stack_is_empty(stack s){
    return (s == NULL);
}

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
