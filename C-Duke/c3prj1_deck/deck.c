#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

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

