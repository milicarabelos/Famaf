#ifndef _STRFUNCS_
#define _STRFUNCS_
size_t string_length(const char *str);
// calcula la longitud de la cadena apuntada por str

char *string_filter(const char *str, char c);
/* devuelve una nueva cadena en memoria dinámica que se obtiene tomando los
caracteres de str que son distintos del caracter c. */

#endif