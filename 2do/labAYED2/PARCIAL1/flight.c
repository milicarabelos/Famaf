/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 2;

Flight flight_from_file(FILE* file, char code, unsigned int arrival_hour)
{ 
    int type; 
    Flight flight;
    flight.code = code;
    flight.hour = arrival_hour;

    int res = fscanf(file, EXPECTED_FLIGHT_FILE_FORMAT , &type , &flight.items_amount );

    if (res != AMOUNT_OF_FLIGHT_VARS){
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    //como type es de un tipo enumerado necesito leer el numero del archivo y pasarlo al tipo enumerado item_t segun corresponda
    if (type == 0){
      flight.type = boxes;
    }
    else if (type == 1)
    {
      flight.type = letters;
    }
    //se espera un 0 para cajas o un 1 para cartas cualquier otro formato deberia dar error
    else{
      printf("El formato es distinto al esperado \n");
      exit(EXIT_FAILURE);
    }

    return flight;
}
