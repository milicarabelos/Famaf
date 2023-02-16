#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

pair_t pair_new(int x, int y){
    pair_t p;
    p.fst = x;
    p.snd = y;
    return p;
}

int pair_first(pair_t p){
    return p.fst;
}

int pair_second(pair_t p){
    return p.snd;
}

pair_t pair_swapped(pair_t p){
    pair_t q;
    q.fst = p.snd;
    q.snd = p.fst;
    
    return q;
}

pair_t pair_destroy(pair_t p){
    return p;
}

/* ¿La implementación logra encapsulamiento? ¿Por qué sí? ¿Por qué no? */
// NO logra encapsulamiento porque con pair.h y puedo saber como se implementa pair (con una tupla)