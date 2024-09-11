# test case instruction

## compiling
``` gcc -o main main.c deck.c future.c input.c cards.c ```

## error report
when you complile, you may meet this kind of error report as below. 
> usr/lib/clang/14.0.0/lib/darwin/libclang_rt.osx.a
Undefined symbols for architecture x86_64:
  "_add_card_to", referenced from:
      _add_future_card in future-f30c01.o
      _hand_from_string in input-acd64a.o
  "_add_empty_card", referenced from:
      _hand_from_string in input-acd64a.o
  "_free_deck", referenced from:
      _test_read_input in main-a6892b.o
  "_get_match_counts", referenced from:
      _evaluate_hand in eval-daf094.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)

it means we lose some functions in the symblink files.

because the default symlink files link to the original source directory(c2prj1_cards/, c3prj1_deck/) as below
> lrwxrwxrwx@  1 atom.x  staff    23 10 Sep 10:27 cards.c -> ../c2prj1_cards/cards.c  
> lrwxrwxrwx@  1 atom.x  staff    23 10 Sep 10:27 cards.h -> ../c2prj1_cards/cards.h  
> lrwxrwxrwx@  1 atom.x  staff    21 10 Sep 10:27 deck.c -> ../c3prj1_deck/deck.c  
> lrwxrwxrwx@  1 atom.x  staff    21 10 Sep 10:27 deck.h -> ../c3prj1_deck/deck.h  
> lrwxrwxrwx@  1 atom.x  staff    21 10 Sep 10:27 eval.c -> ../c3prj2_eval/eval.c  
> lrwxrwxrwx@  1 atom.x  staff    21 10 Sep 10:27 eval.h -> ../c3prj2_eval/eval.h

we updated the symlink files(deck.c, eval.c) in the previous assignment c4prj1_deck/, so we have to update the symblink to the new version as below.

> deck.c -> ../c4prj1_deck/c4prj1_deck.c  
> eval.c -> ../c4prj1_deck/c4prj1_eval.c

we updated source files step by step in the past different assignemnt, so we have to update the symlinks also.