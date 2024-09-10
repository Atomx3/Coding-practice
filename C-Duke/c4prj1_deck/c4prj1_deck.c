#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

// this program is originated from ../c3prj1_deck/deck.c in course 3.
// before submmitting the assignment, please delete all symlink files; 
// modifiy this file name to deck.c

// 打印手牌的函数，它接受一个指向deck_t结构的指针。
// 这个结构体包含了一个指向card_t指针数组的指针，以及一个表示牌的数量的size_t类型的变量。
void print_hand(deck_t * hand){
  // 遍历手牌中的每张牌
  for (size_t i = 0; i < hand->n_cards; i++) {
    // 调用print_card函数打印每张牌
    print_card(*hand->cards[i]);
    // 在每张牌后打印一个空格
    printf(" ");
  }
}

// 检查牌组中是否包含特定牌的函数
int deck_contains(deck_t * d, card_t c) {
  // 遍历牌组中的每张牌
  for (size_t i = 0; i < d->n_cards; i++) {
    // 如果找到一张牌的数值和花色都与目标牌相同，则返回1
    if (d->cards[i]->value == c.value && d->cards[i]->suit == c.suit) {
      return 1;
    }
  }
  // 如果没有找到目标牌，则返回0
  return 0;
}

// 洗牌的函数，它接受一个指向deck_t结构的指针
void shuffle(deck_t * d){
  // 只有当牌的数量大于1时才进行洗牌
  if (d->n_cards > 1) {
    // 遍历牌组中的每张牌
    for (size_t i = 0; i < d->n_cards - 1; i++) {
      // 生成一个随机数来选择与当前牌交换的牌
      size_t j = i + rand() / (RAND_MAX / (d->n_cards - i) + 1);
      // 交换两张牌的位置
      card_t *temp = d->cards[j];
      d->cards[j] = d->cards[i];
      d->cards[i] = temp;
    }
  }
}

// 断言检查牌组是否完整的函数
void assert_full_deck(deck_t * d) {
  // 遍历52张标准扑克牌
  for (unsigned i = 0; i < 52; i++) {
    // 从编号生成一张牌
    card_t card = card_from_num(i);
    // 断言牌组中包含这张牌
    assert(deck_contains(d, card));
  }
}

// Below functions work for ../C4PRJ1_DECK/ 
// latter the deck.c has been modified by course 4 ../C4PRJ1_DECK/ 

// 添加特定牌到牌组
void add_card_to(deck_t * deck, card_t c) {
  deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*(deck->cards)));
  deck->cards[deck->n_cards] = malloc(sizeof(*(deck->cards[deck->n_cards])));
  *(deck->cards[deck->n_cards]) = c;
  deck->n_cards++;
}

// 添加一张空牌到牌组
card_t * add_empty_card(deck_t * deck) {
  card_t empty_card = {0, 0};
  add_card_to(deck, empty_card);
  return deck->cards[deck->n_cards - 1];
}

// 创建一个排除特定牌的牌组
deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * new_deck = malloc(sizeof(*new_deck));
  new_deck->cards = NULL;
  new_deck->n_cards = 0;
  for (unsigned i = 0; i < 52; i++) {
    card_t card = card_from_num(i);
    if (!deck_contains(excluded_cards, card)) {
      add_card_to(new_deck, card);
    }
  }
  return new_deck;
}

// 构建剩余牌组
deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * all_cards = malloc(sizeof(*all_cards));
  all_cards->cards = NULL;
  all_cards->n_cards = 0;
  for (size_t i = 0; i < n_hands; i++) {
    for (size_t j = 0; j < hands[i]->n_cards; j++) {
      add_card_to(all_cards, *(hands[i]->cards[j]));
    }
  }
  deck_t * remaining_deck = make_deck_exclude(all_cards);
  free_deck(all_cards);
  return remaining_deck;
}

// 释放牌组内存
void free_deck(deck_t * deck) {
  for (size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
