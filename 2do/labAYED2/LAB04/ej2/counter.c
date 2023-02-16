#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter c=NULL;
    c = malloc(sizeof(struct _counter));
    c->count  = 0;
    assert(counter_is_init(c));
    return c;
}

void counter_inc(counter c) {
    assert(c!=NULL);
    c->count = c->count + 1;
}

bool counter_is_init(counter c) {
        assert(c!=NULL);
return (0 == c->count);
}

void counter_dec(counter c) {
    assert(c!=NULL);
    assert(!(counter_is_init(c)));
    c->count = c->count - 1;
}

counter counter_copy(counter c) {
    counter q;
    assert(c!=NULL);
    q =  malloc(sizeof(struct _counter));
    q->count = c->count;
    return q;
}

void counter_destroy(counter c) {
    assert(c!=NULL);
    free(c);
}
