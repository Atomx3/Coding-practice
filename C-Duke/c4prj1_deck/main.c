#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "eval.h"

// there is no main.c in the original source files 
// so we add main.c for test case, don't submite it as assignment.

void test_add_card_to() {
    deck_t *deck = malloc(sizeof(*deck));
    deck->cards = NULL;
    deck->n_cards = 0;

    card_t card1 = {VALUE_ACE, SPADES};
    card_t card2 = {VALUE_KING, HEARTS};
    add_card_to(deck, card1);
    add_card_to(deck, card2);

    printf("Deck after adding cards:\n");
    print_hand(deck);
    printf("\n");

    free_deck(deck);
}

void test_make_deck_exclude() {
    deck_t *excluded = malloc(sizeof(*excluded));
    excluded->cards = NULL;
    excluded->n_cards = 0;

    card_t card1 = {VALUE_ACE, SPADES};
    card_t card2 = {VALUE_KING, HEARTS};
    add_card_to(excluded, card1);
    add_card_to(excluded, card2);

    deck_t *new_deck = make_deck_exclude(excluded);

    printf("Excluded deck:\n");
    print_hand(excluded);
    printf("\nNew deck excluding above cards:\n");
    print_hand(new_deck);
    printf("\n");

    free_deck(excluded);
    free_deck(new_deck);
}

void test_build_remaining_deck() {
    deck_t *hand1 = malloc(sizeof(*hand1));
    hand1->cards = NULL;
    hand1->n_cards = 0;
    add_card_to(hand1, (card_t){VALUE_ACE, SPADES});
    add_card_to(hand1, (card_t){VALUE_KING, HEARTS});

    deck_t *hand2 = malloc(sizeof(*hand2));
    hand2->cards = NULL;
    hand2->n_cards = 0;
    add_card_to(hand2, (card_t){VALUE_QUEEN, DIAMONDS});
    add_card_to(hand2, (card_t){VALUE_JACK, CLUBS});

    deck_t *hands[] = {hand1, hand2};
    deck_t *remaining_deck = build_remaining_deck(hands, 2);

    printf("Hand 1:\n");
    print_hand(hand1);
    printf("\nHand 2:\n");
    print_hand(hand2);
    printf("\nRemaining deck:\n");
    print_hand(remaining_deck);
    printf("\n");

    free_deck(hand1);
    free_deck(hand2);
    free_deck(remaining_deck);
}

void test_get_match_counts() {
    deck_t *hand = malloc(sizeof(*hand));
    hand->cards = NULL;
    hand->n_cards = 0;
    add_card_to(hand, (card_t){VALUE_ACE, SPADES});
    add_card_to(hand, (card_t){VALUE_ACE, HEARTS});
    add_card_to(hand, (card_t){VALUE_KING, DIAMONDS});
    add_card_to(hand, (card_t){VALUE_KING, CLUBS});
    add_card_to(hand, (card_t){VALUE_KING, SPADES});

    unsigned *match_counts = get_match_counts(hand);

    printf("Hand:\n");
    print_hand(hand);
    printf("\nMatch counts:\n");
    for (size_t i = 0; i < hand->n_cards; i++) {
        printf("%u ", match_counts[i]);
    }
    printf("\n");

    free(match_counts);
    free_deck(hand);
}

int main(void) {
    test_add_card_to();
    test_make_deck_exclude();
    test_build_remaining_deck();
    test_get_match_counts();
    return 0;
}
