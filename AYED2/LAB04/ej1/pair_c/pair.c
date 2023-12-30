#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */
struct s_pair_t {
    int fst;
    int snd;
};

pair_t pair_new(int x, int y){
    pair_t p;
    p = malloc(sizeof(struct s_pair_t));
    p->fst = x;
    p->snd = y;
    return p;
}

int pair_first(pair_t p){
return p->fst;
}

int pair_second(pair_t p){
return p->snd;
}

pair_t pair_swapped(pair_t p){
    pair_t q;
    q = malloc(sizeof(struct s_pair_t));
    q->fst = p->snd;
    q->snd = p->fst;
    return q;
}

pair_t pair_destroy(pair_t p){
   free(p);
   return NULL; 
}

/* ¿La implementación logra encapsulamiento? ¿Por qué sí? ¿Por qué no? */
//la implementacion logra encapsulamiento porque con pair.h NO puedo saber como se implementa pair y me limito a utilizarla con sus funciones definidas