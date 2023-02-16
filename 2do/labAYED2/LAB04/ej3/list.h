#ifndef _LIST_H
#define _LIST_H

typedef struct node * list;
typedef int type;

//CONSTRUCTORES

list empty(void);
//crea una lista vacia

list addl(list lista, type n);
//agrega un elemento al comienzo de la lista

//OPERACIONES
bool is_empty(list lista);
//devuelve true si la lista es vacia 

type head(list lista);
//devuelve el primer elemento de la lista

list tail(list lista);
//elimina el primer elemento de la lista

list addr(list lista, type n);
//agrega un elemento al final de la lista

int lenght (list lista);
//devuelve la cantidad de elementos de la lista

list concat(list lista1, list lista2);
//concatena la segunda lista a al primera

type index(list lista, int n);
//devuelve el elemento en la enesima posicion

list take(list lista, int n);
//deja los n primeros elementos eliminando el resto

list drop(list lista, int n);
//elimina los n primeros elementos

list copy(list lista);
//copia la lista 

//DESTROY
void destroy(list lista);
//libera memoria, destruye la lista
#endif 