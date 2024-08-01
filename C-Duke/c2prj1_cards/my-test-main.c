#include "cards.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Test the assert_card_valid function
  card_t test_card = { .value = 2, .suit = SPADES };
  assert_card_valid(test_card);
  printf("Card is valid.\n");

  // Test the ranking_to_string function
  printf("STRAIGHT_FLUSH: %s\n", ranking_to_string(STRAIGHT_FLUSH));
  printf("FOUR_OF_A_KIND: %s\n", ranking_to_string(FOUR_OF_A_KIND));
  printf("FULL_HOUSE: %s\n", ranking_to_string(FULL_HOUSE));

  // Test the value_letter function
  printf("Value letter for Ace: %c\n", value_letter((card_t){ .value = VALUE_ACE, .suit = SPADES }));
  printf("Value letter for King: %c\n", value_letter((card_t){ .value = VALUE_KING, .suit = SPADES }));

  // Test the suit_letter function
  printf("Suit letter for Spades: %c\n", suit_letter((card_t){ .value = 2, .suit = SPADES }));
  printf("Suit letter for Hearts: %c\n", suit_letter((card_t){ .value = 2, .suit = HEARTS }));

  // Test the print_card function
  card_t ace_of_spades = { .value = VALUE_ACE, .suit = SPADES };
  printf("Print Ace of Spades: ");
  print_card(ace_of_spades);
  printf("\n");

  // Test the card_from_letters function
  card_t card_from_let = card_from_letters('A', 's');
  printf("Card from letters (As): ");
  print_card(card_from_let);
  printf("\n");

  // Test the card_from_num function
  card_t card_from_n = card_from_num(0);
  printf("Card from number (0): ");
  print_card(card_from_n);
  printf("\n");

  return 0;
}

