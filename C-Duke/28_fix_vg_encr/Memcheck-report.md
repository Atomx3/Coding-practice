// how to save output of command lines in unix terminal?

// below does't work
// ``` valgrind --track-origins=yes ./encrypt 7 input.txt | tee Memcheck-report.md ```
// ``` valgrind --track-origins=yes ./encrypt 7 input.txt >> Memcheck-report.md ```

// below does work
// ``` script Memcheck-report.md ```
// ``` valgrind --track-origins=yes ./encrypt 7 input.txt ```
// after finish the job, input ``` exit ``, otherwise the 
// script will always keep recording of your operation in terminal.

Script started on Fri Aug 30 19:59:57 2024
[1m[7m%[27m[1m[0m                                                                                             
 
]7;file://path***/28_fix_vg_encr
[0m[27m[24m[Jatom.x@atomx 28_fix_vg_encr % [K[?2004h[7mvalgrind --track-origins=yes ./encrypt 7 input.txt[27m

[K[A[35C[27mv[27ma[27ml[27mg[27mr[27mi[27mn[27md[27m [27m-[27m-[27mt[27mr[27ma[27mc[27mk[27m-[27mo[27mr[27mi[27mg[27mi[27mn[27ms[27m=[27my[27me[27ms[27m [27m.[27m/[27me[27mn[27mc[27mr[27my[27mp[27mt[27m [27m7[27m [27mi[27mn[27mp[27mu[27mt[27m.[27mt[27mx[27mt[1B
[K[A[85C[?2004l[1B

==5392== Memcheck, a memory error detector
==5392== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==5392== Using Valgrind-3.23.0.GIT-lbmacos and LibVEX; rerun with -h for copyright info
==5392== Command: ./encrypt 7 input.txt
==5392== 
==5392== 
==5392== HEAP SUMMARY:
==5392==     in use at exit: 8,200 bytes in 162 blocks
==5392==   total heap usage: 169 allocs, 7 frees, 16,494 bytes allocated
==5392== 
==5392== LEAK SUMMARY:
==5392==    definitely lost: 4,160 bytes in 130 blocks
==5392==    indirectly lost: 0 bytes in 0 blocks
==5392==      possibly lost: 576 bytes in 2 blocks
==5392==    still reachable: 3,464 bytes in 30 blocks
==5392==         suppressed: 0 bytes in 0 blocks
==5392== Rerun with --leak-check=full to see details of leaked memory
==5392== 
==5392== For lists of detectedmmake[?2004l

gcc -ggdb3 -Wall -Werror -std=gnu99 -pedantic -o encrypt encrypt.c
[1m[7m%[27m[1m[0m                                                                                             
 
]7;file://path***/28_fix_vg_encr
[0m[27m[24m[Jatom.x 28_fix_vg_encr % [K[?2004h[7mvalgrind --track-origins=yes ./encrypt 7 input.txt[27m[50D[27mv[27ma[27ml[27mg[27mr[27mi[27mn[27md[27m [27m-[27m-[27mt[27mr[27ma[27mc[27mk[27m-[27mo[27mr[27mi[27mg[27mi[27mn[27ms[27m=[27my[27me[27ms[27m [27m.[27m/[27me[27mn[27mc[27mr[27my[27mp[27mt[27m [27m7[27m [27mi[27mn[27mp[27mu[27mt[27m.[27mt[27mx[27mt[?2004l

==5944== Memcheck, a memory error detector
==5944== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==5944== Using Valgrind-3.23.0.GIT-lbmacos and LibVEX; rerun with -h for copyright info
==5944== Command: ./encrypt 7 input.txt
==5944== 
==5944== 
==5944== HEAP SUMMARY:
==5944==     in use at exit: 8,200 bytes in 162 blocks
==5944==   total heap usage: 169 allocs, 7 frees, 16,494 bytes allocated
==5944== 
==5944== LEAK SUMMARY:
==5944==    definitely lost: 4,160 bytes in 130 blocks
==5944==    indirectly lost: 0 bytes in 0 blocks
==5944==      possibly lost: 576 bytes in 2 blocks
==5944==    still reachable: 3,464 bytes in 30 blocks
==5944==         suppressed: 0 bytes in 0 blocks
==5944== Rerun with --leak-check=full to see details of leaked memory
==5944== 
==5944== For lists of detected and suppressed errors, rerun with: -s
==5944== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 104 from 19)
[1m[7m%[27m[1m[0m                                                             

/*                                                              The message ==6179== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 104 from 19) indicates that Valgrind did not find any errors in your code during this run. The “suppressed” part refers to errors that Valgrind is configured to ignore, which is common and usually not a concern.

It looks like your code is running cleanly without any memory errors. Great job! 🎉
*/            

Saving session...
...saving history...truncating history files...
...completed.

Script done on Fri Aug 30 20:44:58 2024
