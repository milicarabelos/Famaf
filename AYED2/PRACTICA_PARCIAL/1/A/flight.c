/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 3 ;

Flight flight_from_file(FILE* file, char code)
{
    Flight flight;
    unsigned int type;
    flight.code = code;
    int res = fscanf(file , "%u %u %u ", &type, &flight.hour, &flight.passengers_amount);
    if (type == 0){
      flight.type = arrival;
    }
    else
    {
      flight.type = departure;
    }

    if (res != AMOUNT_OF_FLIGHT_VARS){
    fprintf(stderr, "Invalid array.\n");
    exit(EXIT_FAILURE);
    }
    return flight;
}
