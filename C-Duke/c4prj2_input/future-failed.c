// I failed by this program, but GPT said it is perfect solution.

#include <stdio.h>
#include <stdlib.h>
#include "future.h"
#include "deck.h"

// Adds a future card to the future_cards_t structure
void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if (index >= fc->n_decks) {
    fc->decks = realloc(fc->decks, (index + 1) * sizeof(*fc->decks));
    for (size_t i = fc->n_decks; i <= index; i++) {
      fc->decks[i].cards = NULL;
      fc->decks[i].n_cards = 0;
    }
    fc->n_decks = index + 1;
  }
  add_card_to(&fc->decks[index], *ptr);  // Dereference ptr here
}

// Assigns cards from the deck to the placeholders in future_cards_t
void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  if (deck->n_cards < fc->n_decks) {
    fprintf(stderr, "Not enough cards in the deck to fill future cards\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < fc->n_decks; i++) {
    for (size_t j = 0; j < fc->decks[i].n_cards; j++) {
      fc->decks[i].cards[j]->value = deck->cards[i]->value;
      fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
    }
  }
}
