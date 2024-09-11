#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"
// this solution output the result answers2.txt that is really closed to standard answers.
// we should make `deck_t ** decks;` in future.h that will suit for this program.
// why ?

int main(int argc, char ** argv) {
  if (argc < 2 || argc > 3) {
    fprintf(stderr, "Usage: %s <input file> [num trials]\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Read input file
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open input file");
    return EXIT_FAILURE;
  }

  size_t n_hands = 0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  deck_t ** hands = read_input(f, &n_hands, fc);
  fclose(f);

  // Create the remaining deck
  deck_t * remaining_deck = build_remaining_deck(hands, n_hands);

  // Set number of trials
  size_t num_trials = (argc == 3) ? atoi(argv[2]) : 10000;

  // Initialize win counts array
  unsigned * win_counts = calloc(n_hands + 1, sizeof(*win_counts));

  // Monte Carlo simulation
  for (size_t i = 0; i < num_trials; i++) {
    shuffle(remaining_deck);
    future_cards_from_deck(remaining_deck, fc);

    int winning_index = 0;
    int tie = 0;
    for (size_t j = 1; j < n_hands; j++) {
      int cmp = compare_hands(hands[j], hands[winning_index]);
      if (cmp > 0) {
        winning_index = j;
        tie = 0;
      } else if (cmp == 0) {
        tie = 1;
      }
    }
    if (tie) {
      win_counts[n_hands]++;
    } else {
      win_counts[winning_index]++;
    }
  }

  // Print results
  printf("%s: ", argv[1]);
  for (size_t i = 0; i < n_hands; i++) {
    unsigned percentage = (unsigned)((win_counts[i] * 100.0 / num_trials) + 0.5);
    printf("Hand %zu = %u%%", i, percentage);
    if (i < n_hands - 1) {
      printf(", ");
    }
  }
  printf("\n");

  // Print tie results
  //printf("And there were %u ties\n", win_counts[n_hands]);

  // Free memory
  for (size_t i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);
  free_deck(remaining_deck);
  free(win_counts);
  free(fc->decks);
  free(fc);

  return EXIT_SUCCESS;
}
