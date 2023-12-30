/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last entry in flight table
* @return True when is the last entre of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DeliveryTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour - 1);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int extra_space_fee_cost (DeliveryTable a, unsigned int h) {
  int boxes,letters,ext_boxes,ext_letters;
  boxes = 0;
  letters = 0;
  ext_boxes = 0;
  ext_letters = 0;

  //cuento la cantidad de cajas que hay hasta las 8pm (incluidas)
  for (unsigned int i = 0; i <= h ; i++)
  {
    boxes = boxes + a[0][i].items_amount;
  }

  //cuento la cantidad de cartas que hay hasta las 8pm (incluidas)
  for (unsigned int i = 0; i <= 20 ; i++)
  {
    letters = letters + a[1][i].items_amount;
  }

  //si me paso del maximo de cartas me fijo por cuanto
  if (letters > MAX_ALLOWED_LETTERS){
    ext_letters = letters - MAX_ALLOWED_LETTERS;
  }
  
  //si me paso del maximo de cajas me fijo por cuanto
  if (boxes > MAX_ALLOWED_BOXES){
    ext_boxes = boxes - MAX_ALLOWED_BOXES;
  }

  //calculo el impuesto
  return ((ext_boxes * BOX_PENALTY) + (ext_letters * LETTER_PENALTY));
} 


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  unsigned int arrival_hour;
  int i = 0;

  while (!feof(file)) {
    int res = fscanf(file, "_%c_", &code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }

    int res1 = fscanf(file, "%u", &arrival_hour);
    if (res1 != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    //Mis horas van desde 0-23 y no puedo tener mas de 24 horas en un dia 
    if (i>23 ){
      printf("el archivo es demasiado grande \n");
      exit(EXIT_FAILURE);
    }
    /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
    Flight flight_boxes = flight_from_file(file, code, arrival_hour);
    Flight flight_letters =flight_from_file(file, code, arrival_hour);

    array[0][arrival_hour-1]= flight_boxes ;
    array[1][arrival_hour-1] = flight_letters;
    i++;
  }
}
