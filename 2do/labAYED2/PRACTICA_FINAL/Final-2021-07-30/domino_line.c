#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "domino_line.h"
#include "domino.h"

struct _s_line
{
    domino elem;
    struct _s_line *next;
    unsigned int size;
};

domino_line line_new(domino first)
{
    domino_line line = calloc(1, sizeof(struct _s_line));
    line->elem = first;
    line->next = NULL;
    line->size = 1;
    return line;
}

domino_line line_add(domino_line line, domino t)
{
    assert(line != NULL);

    domino_line aux = line;

    while (aux->next != NULL)
    {
        aux = aux->next;
    }

    struct _s_line *newtile = calloc(1, sizeof(struct _s_line));
    assert(newtile != NULL);
    newtile->elem = t;
    newtile->next = NULL;

    aux->next = newtile;
    line->size++;

    return line;
}

unsigned int line_length(domino_line line)
{
    return line->size;
}

bool line_n_correct(domino_line line, unsigned int n)
{   
    bool correct = true;

    if (n == 0)
    {
        if(line->next == NULL){
            correct = true;
        }
        else{
            correct = domino_down(line->elem) == domino_up(line->next->elem);
        }
    }   
    else if (n == line->size-1)
    {   
        domino_line aux=line;

        for (unsigned int i = 1; i < n ; i++)
        {   
            aux = aux->next;
        }

        correct = domino_down(aux->elem) == domino_up(aux->next->elem);
    } 
    else{
        
        domino_line aux=line;

        for (unsigned int i = 1; i < n ; i++)
        {   
            aux = aux->next;
        }

        correct = (domino_down(aux->elem) == domino_up(aux->next->elem)) &&( domino_down(aux->next->elem) == domino_up(aux->next->next->elem));

    }
    return correct;
}

int line_total_points(domino_line line)
{
    int points = 0;
    domino_line aux = line;
    while (aux!=NULL)
    {
        points = points + domino_up(aux->elem) + domino_down(aux->elem);
        aux = aux->next;
    }

    return points;
}

domino *line_to_array(domino_line line)
{
    domino *array = calloc(line->size,sizeof(domino));
    assert(array !=NULL);
    domino_line aux=line;

    for (unsigned int i = 0; i < line->size; i++)
    {
        array[i] = aux->elem;
        aux = aux->next;
    }
    assert(aux == NULL);

    return array;
}

void line_dump(domino_line line)
{
    domino *array = line_to_array(line);
    for (unsigned int i = 0u; i < line_length(line); i++)
    {
        domino_dump(array[i]);
    }
    free(array);
}

domino_line line_destroy(domino_line line)
{
    while (line != NULL)
    {
        domino_line aux=line;
        line = line->next;
        domino_destroy(aux->elem);
        free(aux);
        aux = NULL;
    }
    
    return line;
}
