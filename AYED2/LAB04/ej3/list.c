
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"


struct node
{
    type elem;
    struct node *next;
};

list empty()
{
    return NULL;
}

list addl(list lista, type n)
{
    struct node *p = NULL;
    p = malloc(sizeof(struct node));
    p->elem = n;
    p->next = lista;
    lista = p;
    return lista;
}

// OPERACIONES
bool is_empty(list lista)
{
    return (lista == NULL);
}

type head(list lista)
{
    assert(!is_empty(lista));
    return lista->elem;
}

list tail(list lista)
{   assert(!is_empty(lista));
    struct node *p = NULL;
    p = lista;
    lista = lista->next;
    free(p);
    return lista;
}

list addr(list lista, type n)
{
    struct node *q = NULL;
    q = malloc(sizeof(struct node));
    q->elem = n;
    q->next = NULL;
    if (!is_empty(lista)){
        struct node *p = NULL;
        p = lista;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = q;
    }
    else
    {
        lista = q;
    }
    return lista;
}

int lenght(list lista)
{
    int n = 0;
    struct node *p = NULL;
    p = lista;
    while (p != NULL)
    {
        n = n + 1;
        p = p->next;
    }
    
    return n;
}

list concat(list lista1, list lista2)
{   struct node *l2;
    l2 = copy(lista2);

    if (!is_empty(lista1)){

        struct node *p = NULL;
        p = lista1;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = l2;
    }
    else
    {
        lista1 = l2;
    }
    return lista1;
}

type index(list lista, int n)
{   
    assert(lenght(lista)>=n);
    struct node *p = NULL;
    int cont = 1;
    p = lista;  
    while (cont < n)
    {
        cont++;
        p = p->next;
    }
    int elemento = p->elem;
    return elemento;
}

list take(list lista, int n)
{
    struct node *p = lista;
    struct node *q = NULL;

    // voy a “avanzar” el puntero p hasta el elemento n+1
    for (int i = 1; i != n-1; i++)
    {
        if (p != NULL)
        {
            p = p->next;
        }
    }

    if (p != NULL)
    {
        q = p;
        p = p->next;
        q->next = NULL;
    }

    while (p != NULL){ 
        q = p;
        p = p->next;
        free(q);
    }

    return lista;
}

list drop(list lista, int n){
    struct node *p=NULL;
    int cont=0;

    while (cont<n)
    {
        p=lista;
        lista=lista->next;
        free(p);
        cont ++;
    }
    return lista;
    
}

list copy(list lista){
    struct node *p;
    int n=0;
    p = lista;

    while (n != lenght(lista))
    {
        p->next = lista->next;
        p->elem = lista->elem;
        n++;
    }

    return p;
}

// DESTROY
void destroy(list lista){
    struct node *p=NULL;

    while (lenght(lista) > 0){
        p=lista;
        lista=lista->next;
        free(p);
    } 
}