#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"
//#include "deck.h"
// Char 'T' is invalid in this program, '0'represents value 10.

void assert_card_valid(card_t c) {
  assert(c.value>=2 && c.value <=VALUE_ACE);
  assert(c.suit>=SPADES && c.suit<=CLUBS);

}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r){
  case STRAIGHT_FLUSH:
    return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND:
    return "FOUR_OF_A_KIND";
  case FULL_HOUSE:
    return "FULL_HOUSE";
  case FLUSH:
    return "FLUSH";
  case STRAIGHT:
    return "STRAIGHT";
  case THREE_OF_A_KIND:
    return "THREE_OF_A_KIND";
  case TWO_PAIR:
    return "TWO_PAIR";
  case PAIR:
    return "PAIR";
  case NOTHING:
    return "NOTHING";
  default:
    return "NO_SUCH_COMBINATION";
  }
  }


// Returns the character representing the value of the card
char value_letter(card_t c) {
  if (c.value >= 2 && c.value <= 9) {
    return '0' + c.value; // Convert numerical value to character
  }
  switch(c.value) {
    case 10: return '0';// handle 10, use '0' not 'T'.
    case VALUE_JACK: return 'J';
    case VALUE_QUEEN: return 'Q';
    case VALUE_KING: return 'K';
    case VALUE_ACE: return 'A';
    default: return '?' ;
  }
}


char suit_letter(card_t c) {
  switch(c.suit){
  case SPADES: return 's';
  case HEARTS: return 'h';
  case DIAMONDS: return 'd';
  case CLUBS: return 'c';
  default: return '?';
  }
}


// Prints the card in a human-readable format
void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c)); // Use value_letter and suit_letter to print card
}
// Creates a card_t from a pair of characters representing value and suit
card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  if (value_let >= '2' && value_let <= '9') {
    temp.value = value_let - '0'; // Convert numerical value to integer
  } else {
  switch(value_let) {
    case '0': temp.value = 10; break;// handle 10, use'0', not "T".
    case 'J': temp.value = VALUE_JACK; break;
    case 'Q': temp.value = VALUE_QUEEN; break;
    case 'K': temp.value = VALUE_KING; break;
    case 'A': temp.value = VALUE_ACE; break;
    default:
       fprintf(stderr, "Error: Invalid value character '%c'\n", value_let);
       exit(EXIT_FAILURE);
		}
}
  switch(suit_let) {
    case 's': temp.suit = SPADES; break;
    case 'h': temp.suit = HEARTS; break;
    case 'd': temp.suit = DIAMONDS; break;
    case 'c': temp.suit = CLUBS; break;
    default:
      fprintf(stderr, "Error: Invalid suit character '%c'\n", suit_let);
      exit(EXIT_FAILURE);
  }
  assert_card_valid(temp); // Check if the created card is valid
  return temp;
}


card_t card_from_num(unsigned c) {
  card_t ret_card;
  int suit=c/13;
  int value=c%13;
  // assign cards to numbers as such: 0-12 are values 2-14 on suit SPADES,
  // 13-25 suit HEARTS
  // 26-38 suit DIAMONDS
  // 39-51 suit CLUBS
  switch(suit){
  case 0:
    ret_card.suit=SPADES;
    break;
  case 1:
    ret_card.suit=HEARTS;
    break;
  case 2:
    ret_card.suit=DIAMONDS;
    break;
  case 3:
    ret_card.suit=CLUBS;
    break;
    
  }

  //
  if (value>=2){
    ret_card.value=value;
  }else{
    ret_card.value=value+13;
  }
  
  return ret_card;
}

