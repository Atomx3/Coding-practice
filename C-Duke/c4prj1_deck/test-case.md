## add main.c
there is no main.c in the original source files 
so we add main.c for test case.

## compile program 
```gcc -o poker_program main.c deck.c eval.c cards.c -Wall -Werror```

```./poker_program```

## output results
Deck after adding cards:
As Kh
Excluded deck:
As Kh
New deck excluding above cards:
Ks 2s 3s 4s 5s 6s 7s 8s 9s 0s Js Qs Ah 2h 3h 4h 5h 6h 7h 8h 9h 0h Jh Qh Kd Ad 2d 3d 4d 5d 6d 7d 8d 9d 0d Jd Qd Kc Ac 2c 3c 4c 5c 6c 7c 8c 9c 0c Jc Qc
Hand 1:
As Kh
Hand 2:
Qd Jc
Remaining deck:
Ks 2s 3s 4s 5s 6s 7s 8s 9s 0s Js Qs Ah 2h 3h 4h 5h 6h 7h 8h 9h 0h Jh Qh Kd Ad 2d 3d 4d 5d 6d 7d 8d 9d 0d Jd Kc Ac 2c 3c 4c 5c 6c 7c 8c 9c 0c Qc
Hand:
As Ah Kd Kc Ks
Match counts:
2 2 3 3 3

It looks like your tests are running successfully! Here’s a summary of what each test is doing:

1. **Deck after adding cards**:
   - You added `As` (Ace of Spades) and `Kh` (King of Hearts) to the deck, and it printed correctly.

2. **Excluded deck**:
   - You created a deck excluding `As` and `Kh`. The new deck correctly excludes these cards and includes the remaining 50 cards.

3. **Remaining deck**:
   - You created two hands and built the remaining deck. The remaining deck correctly excludes the cards from both hands.

4. **Match counts**:
   - You created a hand with `As Ah Kd Kc Ks` and printed the match counts. The counts are correct: `2 2 3 3 3`, indicating two Aces and three Kings.

If you want to further test your program, you can add more complex scenarios or edge cases. For example, you could test:

- Adding more cards to the deck and ensuring no duplicates.
- Creating hands with different combinations of cards to test the `get_match_counts` function more thoroughly.
- Testing the `evaluate_hand` function with various poker hands to ensure it correctly identifies hand rankings.

If you have any specific scenarios you'd like to test or if you encounter any issues, feel free to ask!