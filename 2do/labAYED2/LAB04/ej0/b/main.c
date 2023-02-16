#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

void set_name(name_t new_name, data_t *d) {

    for (unsigned int i = 0; i < 30; i++)
    {
        d->name[i] = new_name[i]; 
    }
    
}

int main(void) {
    data_t *d=NULL ;
    
/*      d = malloc(sizeof(data_t)); 
 */
    data_t messi = {"Leo Messi",  34, 169};
    print_data(messi);
    d = &messi;

/*     printf("%p \n", d);
    printf("another one %p \n", &messi); */
    name_t messi_full_name = "Lionel Messi";
    
    set_name (messi_full_name, d);
    print_data(messi);
    
    return EXIT_SUCCESS;
}

