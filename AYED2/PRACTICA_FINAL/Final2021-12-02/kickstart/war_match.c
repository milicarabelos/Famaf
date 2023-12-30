#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "war_match.h"
#include "card.h"

struct _s_match {
  card c;
  war_match next;
};

war_match match_new(void) {
  /* initially the match is empty */
  return NULL;
}

war_match match_add(war_match match, card c) {
  assert(c!=NULL);
  assert(1 <= card_number(c) && card_number(c) <= 13);
  
  char card_s;
  unsigned player;
  card_s = card_suit(c);
  player = card_player(c);

  assert(card_s == 'd' || 't' || 'c' || 'p');
  assert(player == 1 || 2);
  
  war_match new_card;
  new_card = malloc(sizeof(struct _s_match));
  new_card->c = c;
  new_card->next = NULL;

  if (match == NULL) {
    match = new_card;
  } else {
    war_match aux = match;
    // Recorro hasta la carta top del mazo, la q esta arriba del todo
    while (aux->next != NULL) {
      aux = aux->next;
    }
    aux->next = new_card;
    aux = NULL;
  }

  return match;
}

unsigned int match_size(war_match match) {
  unsigned int size;
  war_match aux;
  size = 0u;
  if (match != NULL) {
    aux = match;
    while (aux != NULL) {
      size++;
      aux = aux->next;
    }
  }
  return size;
}

unsigned int match_length(war_match match) {
  unsigned int length;
  length = 0u;
  if (is_match_correct(match) && (match_size(match)%2==0)) {
    length = match_size(match)/2;
  }
 
  return length;
}

bool is_match_correct(war_match match) {
  bool valid;
  unsigned int actual_player, next_player;
  unsigned int size;
  war_match aux;

  valid = false;
  size = match_size(match);
  
  
  /* El jugador 1 inició la partida. */
  valid = (card_player(match->c) == 1);
  
  /* La cantidad de cartas es par. */
  valid = valid && size%2==0;

  /* Cada carta c del jugador 1, está seguida de una carta c’ del jugador 2. */
  aux = match;
  while (valid && aux->next != NULL) {
    /* Tomo la carta del jugador actual */
    actual_player = card_player(aux->c);
    /* Tomo la carta del siguiente jugador */
    next_player = card_player(aux->next->c);
    if (actual_player==1 && next_player==2) {
      valid = true;
    } else if (actual_player==2 && next_player==1) {
      valid = true;
    } else if (actual_player==next_player) {
      /* Nunca dos cartas contiguas pertenecen al mismo jugador.*/
      valid = false;
    }
    aux = aux->next;
  }
  return valid;
}

static unsigned int player_score(war_match match, unsigned int player) {
  /*
  * Calcula el puntaje de 'player' en el partido 'match'
  */

  /*En cada mano, al jugador con la carta de valor numérico mayor, 
    se le suman los puntos de la carta de valor numérico menor. 
    Si la carta del primer jugador es mayor a la del segundo,
    se le asignan los puntos del segundo, con la funcion
    card_match_points.
    */

  unsigned int score;
  war_match aux;
 
  score = 0u;
  aux = match;

  while (aux != NULL) {
    // La carta es del primer jugador
    if (player==1 && card_player(aux->c)==1) {
      // Veo si la carta actual es mayor a la siguiente
      if (card_wins(aux->c, aux->next->c)) {
        // Si gana, se le asignan los puntos de la carta del otro jugador
        score = score + card_match_points(aux->c, aux->next->c);
      } 
    } 
    else if (player==2 && card_player(aux->c)==2) {
      if (card_wins(aux->c, aux->next->c)) {
        score = score + card_match_points(aux->c, aux->next->c);
      }
    }
    aux = aux->next->next;
  }
  aux = NULL;
  return score;
}

unsigned int winner_total_points(war_match match) {
  /*
  * COMPLETAR
  * tips:
  * * recordar que si is_match_correct es falso esto retorna 0
  * * usar player_score para calcular el puntaje de un jugador particular
  *
  */

  unsigned int winner, fst_score, snd_score;
  
  winner = 0u; 
  fst_score = 0u; 
  snd_score = 0u;

  if (is_match_correct(match)) {
    fst_score = player_score(match, 1);
    snd_score = player_score(match, 2);
    if (fst_score > snd_score) {
      winner = fst_score;
    } else if (snd_score > fst_score) {
      winner = snd_score;
    }
  }
  return winner;
}

card * match_to_array(war_match match) {
  card *array;
  war_match aux;
  unsigned int length;
  array = NULL;
  if (match != NULL) {
    length = match_size(match);
    array = calloc(length, sizeof(struct _s_match));
    aux = match;
    for (unsigned int i = 0; i < length; i++) {
      array[i] = aux->c;
      aux = aux->next;
    }
  }
  aux = NULL;
  return array;
}

void match_dump(war_match match) {
  card *array = match_to_array(match);
  for (unsigned int i=0u; i < match_size(match); i++) {
    card_dump(array[i]);
  }
  free(array);
}

war_match match_destroy(war_match match) {
  war_match aux;
  while (match != NULL) {
    aux = match;
    match = match->next;
    aux->c = card_destroy(aux->c);
    free(aux);
  }
  aux = NULL;
  return match;
}
