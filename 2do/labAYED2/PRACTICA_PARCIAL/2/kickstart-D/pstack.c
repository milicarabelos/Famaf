#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

typedef struct s_node *first;

struct s_pstack
{
    priority_t Maxpri;
    first *array;
    unsigned int size;
};

struct s_node
{
    pstack_elem elem;
    struct s_node *next;
};

static struct s_node *create_node(pstack_elem e)
{
    struct s_node *new_node = NULL;
    new_node = calloc(1, sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    free(node);
    node = NULL;
    return node;
}

static bool invrep(pstack s)
{   
    bool b= true;
    if (s->size == 0)
    {
        for (unsigned int i = 0; i < s->Maxpri && b; i++)
        {
            b = s->array[i] == NULL ;
        }
    }
    else
    {   b = false;

        for (unsigned int i = 0; i < s->Maxpri+1 && !(b); i++)
        {
            b = (s->array[i] != NULL);
        }
    }
    return b;
}

pstack pstack_empty(priority_t max_priority)
{
    pstack s = calloc(1, sizeof(struct s_pstack));
    assert(s!=NULL);
    s->array = calloc(max_priority+1,sizeof(first));
    s->Maxpri = max_priority;
    s->size = 0; 
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority)
{
    assert(invrep(s));
    struct s_node *newnode=create_node(e);
    s->size++;

    if (s->array[priority] == NULL)
    {
        s->array[priority] = newnode;
    }
    else
    {   newnode->next=s->array[priority];   
        s->array[priority]=newnode;
    }
    
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s)
{
    assert(invrep(s));
    return s->size == 0;
}

pstack_elem pstack_top(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    pstack_elem elem;
    bool b=true;
    for (int i = s->Maxpri ; i >= 0 && b; i--)
    {
        if (s->array[i] != NULL){
            b = false;
            elem = s->array[i]->elem;
        }
    }
     
    return elem;
}

priority_t pstack_top_priority(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t priority;
    bool b=true;
    for (int i = s->Maxpri ; i >= 0 && b; i--)
    {
        if (s->array[i] != NULL){
            b = false;
            priority = i;
        }
    }
    return priority;
}

size_t pstack_size(pstack s)
{
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));  
    priority_t p = pstack_top_priority(s);

    if (s->array[p]->next == NULL)
    {
        s->array[p]=destroy_node(s->array[p]);
    }
    else
    {
        struct s_node *aux=s->array[p];
        s->array[p]=s->array[p]->next;
        aux = destroy_node(aux);
        assert(aux==NULL);
    }

    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s)
{
    assert(invrep(s));
    while (!pstack_is_empty(s))
    {
        s=pstack_pop(s);
    }
    free(s->array);
    s->array = NULL;
    free(s);
    s=NULL;
    return s;
}
