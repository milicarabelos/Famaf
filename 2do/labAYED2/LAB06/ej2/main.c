#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

int main()
{
    const char word1[] = "carabelos"; //{'c', 'a', 'r', 'a', 'b', 'e', 'l', 'o', 's'}; 
    const char word2[] = "caramelino"; //{'c', 'a', 'r', 'a', 'm', 'e', 'l', 'i', 'n', 'o'}; 

    string s1,s2;
    
    s1 = string_create(word1);
    s2 = string_create(word2);

/*     printf("la w1 es %s", s1);
    printf("la w2 es %s", s2); */

    bool b = string_less(s1,s2);
    bool q = string_eq(s1,s2);

    
    if (b)
    {
        printf("word1 es alfabeticamente menor\n");
    }
    else{
         if (q)
        {
            printf("las palabras son iguales\n");
        }
        else{
        printf("word2 es alfabeticamente menor\n");
        } 
    }
    
    return EXIT_SUCCESS;
} 


  
/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.h"

int main(int argc, char *argv[]) {
  if(argc < 3) {
    fprintf(stderr, "Missing parameters\n");
    exit(EXIT_FAILURE);
  }
  char *word = argv[1];
  char *word2 = argv[2];
  string str = string_create(word);
  string str2 = string_create(word2);
  if(string_eq(str, str2)) {
    printf("Iguales\n");
  } else if(string_less(str, str2)) {
    printf("Menor que\n");
  } else {
    printf("Mayor que\n");
  }

  string_destroy(str);
  string_destroy(str2);
  return 0;
} */