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
      fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour-1);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

 unsigned int extra_space_fee_cost (DeliveryTable a) {
  
  int acum_boxes= 0;
  int ext_boxes= 0;
  int acum_letters= 0;
  int ext_letters= 0;
  int imp;

  for (int i = 0; i <= FEE_CLOSE_HOUR; i++)
  {   
      acum_boxes = acum_boxes + a[0][i].items_amount;
      acum_letters = acum_letters + a[1][i].items_amount;
      //letters + a[1][i].items_amount;
      printf ("la cant de cajas es %d %d \n", acum_boxes, acum_letters);


  }
      ext_boxes = acum_boxes - MAX_ALLOWED_BOXES;
      ext_letters = acum_letters - MAX_ALLOWED_LETTERS;

      if (ext_boxes <= 0)
      {
        imp = ext_letters * LETTER_PENALTY;
      }
      else if (ext_letters <= 0)
      {
        imp = ext_boxes * BOX_PENALTY;
      }
      else 
      {
        imp = (ext_letters*LETTER_PENALTY) + (ext_boxes *BOX_PENALTY);
      }
  return (imp);
} 


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  while (!feof(file)) {
    int res = fscanf(file, "_%c_", &code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    if (i > 24) {
      fprintf(stderr, "The array is too long.\n");
      exit(EXIT_FAILURE);
    }
    /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
    Flight flight_boxes = flight_from_file(file, code, boxes);
    Flight flight_letters = flight_from_file(file, code, letters);

    array[0][flight_boxes.hour-1] = flight_boxes;
    array[1][flight_letters.hour-1] = flight_letters;
    i++;
  }
}
