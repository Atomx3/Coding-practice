// I failed by this program, but GPT said it is perfect solution.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "deck.h"
#include "future.h"

// Parses a single line into a hand
deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * hand = malloc(sizeof(*hand));
  hand->cards = NULL;
  hand->n_cards = 0;

  const char * ptr = str;
  while (*ptr != '\0') {
    if (*ptr == '?') {
      ptr++;
      size_t index = strtoul(ptr, (char **)&ptr, 10);
      card_t * empty_card = add_empty_card(hand);
      add_future_card(fc, index, empty_card);
    } else {
      card_t c = card_from_letters(ptr[0], ptr[1]);
      add_card_to(hand, c);  // Pass c directly
      ptr += 2;
    }
    while (*ptr == ' ' || *ptr == '\n') {
      ptr++;
    }
  }

  if (hand->n_cards < 5) {
    fprintf(stderr, "Error: Hand has fewer than 5 cards\n");
    exit(EXIT_FAILURE);
  }

  return hand;
}

// Reads input from a file and returns an array of hands
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  char * line = NULL;
  size_t sz = 0;
  size_t n = 0;
  deck_t ** hands = NULL;

  while (getline(&line, &sz, f) >= 0) {
    hands = realloc(hands, (n + 1) * sizeof(*hands));
    hands[n] = hand_from_string(line, fc);
    n++;
  }
  free(line);
  *n_hands = n;
  return hands;
}
