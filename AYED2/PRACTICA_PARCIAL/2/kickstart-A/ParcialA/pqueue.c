#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{

    struct s_node *first;
    int index;
};

struct s_node
{
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node *create_node(pqueue_elem e, unsigned int priority)
{
    struct s_node *new_node = NULL;
    // Completar
    new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    /*
     * COMPLETAR
     */
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;

    // assert(e==e && priority == priority); // BORRAR ESTE ASSERT
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    /*
     * COMPLETAR
     *
     */
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep(pqueue q)
{   static bool b = true; 
    if (q->first != NULL && q->first->next != NULL){
    b = q->first->priority <= q->first->next->priority;
    }
    //assert(q == q); // BORRAR ESTE ASSERT
    return b;
}

pqueue pqueue_empty(void)
{
    pqueue q = NULL;
    /*
     * COMPLETAR
     *
     */
    q = malloc(sizeof(struct s_pqueue));
    q->first = NULL;
    q->index = 0;
    assert(invrep(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    /*
     * COMPLETAR
     *
     */

    // assert(e==e && priority==priority && new_node==new_node); // BORRAR ESTE ASSERT
    assert(invrep(q));
    if (pqueue_is_empty(q))
    {
        q->first = new_node;
        q->index = 1;
    }
    else
    {
        if (priority < q->first->priority)
        {
            new_node->next = q->first;
            q->first = new_node;
        }
        else
        {
            struct s_node *aux = NULL;
            // unsigned int count=0;
            
            if (priority > q->first->priority)
            {

                aux = q->first;

                while (aux->next != NULL && priority > aux->next->priority)
                {
                    aux = aux->next;
                    // count ++;
                }
            }

            if (aux == NULL)
            {
                aux = q->first;
                // count = 0;
            }

            if (priority == aux->priority || priority > aux->priority)
            {

                while (aux->next!= NULL && priority == aux->next->priority)
                {
                    aux = aux->next;
                }
            }
            /* aux=NULL;

            for (unsigned int i = 0; i < count-1 ; i++)
            {
                aux =q->first->next;
            }
             */

            new_node->next = aux->next;
            aux->next = new_node;
            aux = NULL;
        }
        q->index = q->index + 1;
    }
    assert(invrep(q));
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    /*
     * COMPLETAR
     *
     */

    // assert(q==q); // BORRAR ESTE ASSERT
    assert(invrep(q));
    bool b = (q->first == NULL && q->index == 0);
    assert(invrep(q));
    return b;
}

pqueue_elem pqueue_peek(pqueue q)
{
    /*
     * COMPLETAR
     *
     */
    // assert(q==q); // BORRAR ESTE ASSERT
    assert(invrep(q));
    return q->first->elem;
}

unsigned int pqueue_peek_priority(pqueue q)
{
    /*
     * COMPLETAR
     *
     */
    // assert(q==q); // BORRAR ESTE ASSERT
    assert(invrep(q));
    return q->first->priority;
}

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    unsigned int size = 0;
    /*
     * COMPLETAR
     *
     */
    size = q->index;
    assert(invrep(q));
    return size;
}

pqueue pqueue_dequeue(pqueue q)
{
    /*
     * COMPLETAR
     *
     */
    // assert(q==q); // BORRAR ESTE ASSERT
    assert(invrep(q));
    struct s_node *p;
    p = q->first;
    q->first = q->first->next;
    free(p);
    p = NULL;
    q->index = q->index - 1;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q));
    /*
     * COMPLETAR
     *
     */
    
    while (q->first != NULL)
    {   
        struct s_node *p;
        p = q->first;
        q->first = q->first->next;
        destroy_node(p);
    }
    
    assert(q->first == NULL);
    free(q);
    return q;
}
