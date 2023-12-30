#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

struct _s_string {
    char *content;
    unsigned int length;
};

string string_create(const char *word) {
    string str = NULL;
    str = calloc(1, sizeof(struct _s_string));
    str->length = 0;
    const char *wordAux = word;
    while ( *wordAux != '\0')
    {     
        //str->content[str->length] = *word;
        wordAux++;
        str->length++;
    }
    wordAux = NULL;
    //str->content[str->length] = '\0';

    str->content = calloc(str->length + 1, sizeof(char));
    str->content = strncpy(str->content, word, str->length + 1);
    return (str);
}

unsigned int string_length(string str) {
    return (str->length);
}

bool string_less(const string str1, const string str2) {
    /* needs implementation */
/*      bool b = true;
     unsigned int lenght = 0;
    if(str1->length < str2->length)
    {
        lenght = str1->length;
    }
    else{
        lenght = str2->length;
    }
    

    for(size_t i = 0; i < lenght && b ; i++)
    {
        b = str1->content[i] <= str2->content[i];
    }
    return b;  */
    bool b =  strcmp(str1->content, str2->content) < 0;
    return (b);
}

bool string_eq(const string str1, const string str2) {
    int cmp = strcmp(str1->content, str2->content);
    return (cmp == 0);
}

string string_clone(const string str) {
    return (string_create(str->content));
}

string string_destroy(string str) {
    free(str->content);
    free(str);
    str = NULL;
    return (str);
}

void string_dump(string str, FILE *file) {
    fprintf(file, "%s", str->content);
}

const char *string_ref(string str) {
    return (str->content);
}
