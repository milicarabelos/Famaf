#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    struct s_node *first;
    int size;
};

struct s_node {
    struct s_node *next;
    pstack_elem elem;
    priority_t priority;

};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    // Completar
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    /*
     * COMPLETAR
     */
    new_node->elem =  e;
    new_node->next = NULL;
    new_node->priority = priority;
    //assert(e==e && priority == priority); // BORRAR ESTE ASSERT
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    /*
     * COMPLETAR
     *
     */
    free(node);
    node=NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    /*
     * COMPLETAR
     *
     */
    //assert(s==s); // BORRAR ESTE ASSERT
    static bool b = true;
    struct s_node *p = NULL;
    p=s->first;
    while (b && (p!=NULL && p->next != NULL)){
        
        b = p->priority >= p->next->priority;
        p = p->next;

    }
    return b;
}

pstack pstack_empty(void) {
    pstack s=NULL;
    /*
     * COMPLETAR
     *
     */
    s = malloc(sizeof(struct s_pstack));
    s->first = NULL;
    s->size = 0;
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    /*
     * COMPLETAR
     *
     */
    s->size ++;
    if ( s->first==NULL || priority >= s->first->priority ){
        new_node->next = s->first;
        s->first = new_node;
    }
    else
    {   struct s_node *aux=NULL;

            aux = s->first;

            while(aux->next != NULL && priority < aux->next->priority)
            {
                aux = aux->next;
            }
 
        

        new_node->next = aux->next;
        aux->next = new_node;
        aux = NULL;
    }
    
    //assert(e==e && priority==priority && new_node==new_node); // BORRAR ESTE ASSERT
    assert(invrep(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    /*
     * COMPLETAR
     *
     */
    
    assert(s==s);
    return (s->size == 0 && s->first == NULL);
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s));
    return s->first->elem;
}

priority_t pstack_top_priority(pstack s) {
    /*
     * COMPLETAR
     *
     */
    //assert(s==s); // BORRAR ESTE ASSERT
    return s->first->priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    //unsigned int size=0;
    /*
     * COMPLETAR
     *
     */
    return s->size;
}

pstack pstack_pop(pstack s) {
    /*
     * COMPLETAR
     *
     */
    assert(!pstack_is_empty(s) && invrep(s));
    
    struct s_node *aux;
    aux = s->first;
    s->first = s->first->next;
    aux = destroy_node(aux);
    s->size = s->size-1;

    //assert(s==s); // BORRAR ESTE ASSERT
    assert(invrep(s));
    return s;

}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    /*
     * COMPLETAR
     *
     */
    while (s->first != NULL)
    {   
        struct s_node *p;
        p=s->first;
        s->first = s->first->next;
        free(p);
        p = NULL;
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

