// there is no main.c in the original source files 
// so we add main.c for test case, don't submite it as assignment.
// this main.c is mainly for the purpose of input function in various unknown cards.
// this main.c is failed to pass some specific test cases, it is not a perfect solution.

#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "future.h"
#include "input.h"

// Define free_future_cards function here
void free_future_cards(future_cards_t * fc) {
  for (size_t i = 0; i < fc->n_decks; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  fc->decks = NULL;
  fc->n_decks = 0;
}

void test_hand_from_string() {
  future_cards_t fc = {NULL, 0};
  const char *str = "As Ks Qs Js 10s ?0 ?1\n";
  deck_t *hand = hand_from_string(str, &fc);

  if (hand == NULL) {
    fprintf(stderr, "hand_from_string failed\n");
    exit(EXIT_FAILURE);
  }

  printf("Hand: ");
  print_hand(hand);
  printf("\n");

  free_deck(hand);
  free_future_cards(&fc);
}

void test_read_input(const char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  size_t n_hands = 0;
  future_cards_t fc = {NULL, 0};
  deck_t **hands = read_input(f, &n_hands, &fc);
  fclose(f);

  if (hands == NULL) {
    fprintf(stderr, "read_input failed\n");
    exit(EXIT_FAILURE);
  }

  printf("Read %zu hands\n", n_hands);
  for (size_t i = 0; i < n_hands; i++) {
    print_hand(hands[i]);
    printf("\n");
    free_deck(hands[i]);
  }
  free(hands);
  free_future_cards(&fc);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Run the test cases
  test_hand_from_string();
  test_read_input(argv[1]);

  return EXIT_SUCCESS;
}

