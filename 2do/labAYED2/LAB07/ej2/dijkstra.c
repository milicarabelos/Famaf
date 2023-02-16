#include <assert.h>
#include <stdlib.h>

#include "cost.h"
#include "graph.h"
#include "mini_set.h"

unsigned int min_pos(set C, cost_t *result, unsigned int max)
{
    cost_t min = cost_inf();
    unsigned int indice;
    for (unsigned int i = 0; i < max; i++)
    {
        if (set_member(i, C))
        {
            if (result[i] < min)
            {
                min = result[i];
                indice = i;
            }
        };
    }
    return indice;
}

cost_t *dijkstra(graph_t graph, vertex_t init)
{
    vertex_t sel;
    set C = set_empty();
    unsigned int max_vertexs = graph_max_vertexs(graph);
    cost_t *result = calloc(max_vertexs, sizeof(cost_t));

    for (unsigned int i = 0; i < max_vertexs; i++)
    {
        C = set_add(C, i);
    }

    C = set_elim(C, init);

    for (unsigned int j = 0; j < max_vertexs; j++)
    {
        result[j] = graph_get_cost(graph, init, j);
    }

    while (!(set_is_empty(C)))
    {
        sel = min_pos(C, result, max_vertexs);
        C = set_elim(C, sel);

        for (unsigned int j = 0; j < max_vertexs; j++)
        {
            if (set_member(j, C))
            {   cost_t costodc = graph_get_cost(graph, sel, j) ; 
                //resolviendo overflow cuando graph_get_cost es inf y result[j] tambien 
                if (graph_get_cost(graph, sel, j)< result[j] - result[sel])
                {
                    result[j] = costodc + result[sel];
                }
            }
        }
    }
    C = set_destroy(C);
    assert(C==NULL);
    return result;
}
