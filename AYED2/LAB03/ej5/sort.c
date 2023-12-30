/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    bool b;
    b = y->rank >= x->rank;
    return b;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

//voy a usar insertionsort 
void sort(player_t a[], unsigned int length) {

    for (unsigned int i = 1u; i < length; ++i) {
        insert(a, i);
        assert(array_is_sorted(a,i));
    }
    
}

void insert(player_t a[], unsigned int i) {
    unsigned int j=i;
    while (j>0 && goes_before(a[j], a[j-1]))
    {
        swap2(a, j, j-1);
        j--;
    }
    
}

void swap2 (player_t a[], int j, int i){
    player_t aux;

    aux = a[j];
    a[j] = a[i];
    a[i] = aux;
}

/* ¿Funciona más rápido la versión con punteros? ¿Por qué son más eficientes los intercambios con esta
versión?
creo que funciona mas eficientemente porque sabemos en que lugar de la memoria estan los datos que necesitamos
y no tenemos que recorrer mas de un player para encontrar el que buscamos 

La última línea de la función main() antes del return llama a destroy() ¿Por qué? ¿Qué ocurriría
si esa línea no estuviera ahí? 
si no estuviera ahi la memoria dinamica que reservamos al utilizar punteros quedaria utilizada y nuestro programa
nos llenaria memoria que luego no utilizaria*/