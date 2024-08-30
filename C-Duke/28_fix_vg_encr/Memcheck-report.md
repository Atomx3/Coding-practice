// how to save output of command lines in unix terminal?

// below does't work
// ``` valgrind --track-origins=yes ./encrypt 7 input.txt | tee Memcheck-report.md ```
// ``` valgrind --track-origins=yes ./encrypt 7 input.txt >> Memcheck-report.md ```

// below does work
// ``` script Memcheck-report.md ```
// ``` valgrind --track-origins=yes ./encrypt 7 input.txt ```


Script started on Fri Aug 30 19:59:57 2024
[1m[7m%[27m[1m[0m                                                                                             
 
]7;file://atomxs-MBP.guests.lan/Users/atom.x/GitHub/Coding-practice/C-Duke/28_fix_vg_encr
[0m[27m[24m[Jatom.x@atomxs-MBP 28_fix_vg_encr % [K[?2004h[7mvalgrind --track-origins=yes ./encrypt 7 input.txt[27m

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
 
]7;file://atomxs-MBP.guests.lan/Users/atom.x/GitHub/Coding-practice/C-Duke/28_fix_vg_encr
[0m[27m[24m[Jatom.x@atomxs-MBP 28_fix_vg_encr % [K[?2004h[7mvalgrind --track-origins=yes ./encrypt 7 input.txt[27m[50D[27mv[27ma[27ml[27mg[27mr[27mi[27mn[27md[27m [27m-[27m-[27mt[27mr[27ma[27mc[27mk[27m-[27mo[27mr[27mi[27mg[27mi[27mn[27ms[27m=[27my[27me[27ms[27m [27m.[27m/[27me[27mn[27mc[27mr[27my[27mp[27mt[27m [27m7[27m [27mi[27mn[27mp[27mu[27mt[27m.[27mt[27mx[27mt[?2004l

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
 
]7;file://atomxs-MBP.guests.lan/Users/atom.x/GitHub/Coding-practice/C-Duke/28_fix_vg_encr
[0m[27m[24m[Jatom.x@atomxs-MBP 28_fix_vg_encr % [K[?2004hcclear[?2004l

[H[2J[1m[7m%[27m[1m[0m                                                                                             
 
]7;file://atomxs-MBP.guests.lan/Users/atom.x/GitHub/Coding-practice/C-Duke/28_fix_vg_encr
[0m[27m[24m[Jatom.x@atomxs-MBP 28_fix_vg_encr % [K[?2004hmmake[?2004l

gcc -ggdb3 -Wall -Werror -std=gnu99 -pedantic -o encrypt encrypt.c
[1m[7m%[27m[1m[0m                                                                                             
 
]7;file://atomxs-MBP.guests.lan/Users/atom.x/GitHub/Coding-practice/C-Duke/28_fix_vg_encr
[0m[27m[24m[Jatom.x@atomxs-MBP 28_fix_vg_encr % [K[?2004h. [7mvalgrind --track-origins=yes ./encrypt 7 input.txt >> outpu[7mt[7m.txt[27m[K

[K[A[A[35C[27mv[27ma[27ml[27mg[27mr[27mi[27mn[27md[27m [27m-[27m-[27mt[27mr[27ma[27mc[27mk[27m-[27mo[27mr[27mi[27mg[27mi[27mn[27ms[27m=[27my[27me[27ms[27m [27m.[27m/[27me[27mn[27mc[27mr[27my[27mp[27mt[27m [27m7[27m [27mi[27mn[27mp[27mu[27mt[27m.[27mt[27mx[27mt[27m [27m>[27m>[27m [27mo[27mu[27mt[27mp[27mut[27m.[27mt[27mx[27mt[1B
[K[A[5C   
t 
[K[A[93C[K[1B
[K[A[93C      [?2004l[1B
==6179== Memcheck, a memory error detector
==6179== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==6179== Using Valgrind-3.23.0.GIT-lbmacos and LibVEX; rerun with -h for copyright info
==6179== Command: ./encrypt 7 input.txt
==6179== 
==6179== 
==6179== HEAP SUMMARY:
==6179==     in use at exit: 8,200 bytes in 162 blocks
==6179==   total heap usage: 169 allocs, 7 frees, 16,494 bytes allocated
==6179== 
==6179== LEAK SUMMARY:
==6179==    definitely lost: 4,160 bytes in 130 blocks
==6179==    indirectly lost: 0 bytes in 0 blocks
==6179==      possibly lost: 576 bytes in 2 blocks
==6179==    still reachable: 3,464 bytes in 30 blocks
==6179==         suppressed: 0 bytes in 0 blocks
==6179== Rerun with --leak-check=full to see details of leaked memory
==6179== 
==6179== For lists of detected and suppressed errors, rerun with: -s
==6179== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 104 from 19)
[1m[7m%[27m[1m[0m                                                                       /*
 The message ==6179== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 104 from 19) indicates that Valgrind did not find any errors in your code durinddiff encrypt
[Jencrypt*            encrypt\ copy.c     encrypt.dSYM/       
encrypt\ copy\ 2.c  encrypt.c           [A[A[0m[27m[24m[35Cdiff encrypt[K cop
[J[A[51Cy 2.c       2.c[1m [0m[0m encrypt1.c[1m [0m[0m [?2004l
[J6,9c6,9
< void encrypt(FILE * f, int key, FILE * outfile){
<   char * line;
<   size_t sz;
<   while (getline(&line,&sz, f) >= 0) {
---
> void encrypt(FILE * f, int key, FILE * outfile) {
>   char * line = NULL;
>   size_t sz = 0;
>   while (getline(&line, &sz, f) != -1) {
14,18c14,18
< 	c = tolower(c);
< 	c -= 'a';
< 	c += key;
< 	c %= 26;
< 	c += 'a';
---
>         c = tolower(c);
>         c -= 'a';
>         c += key;
>         c %= 26;
>         c += 'a';
24a25
>   free(line);
29c30
<     fprintf(stderr,"Usage: encrypt key inputFileName\n");
---
>     fprintf(stderr, "Usage: encrypt key inputFileName\n");
34c35
<     fprintf(stderr,"Invalid key (%s): must be a non-zero integer\n", argv[1]);
---
>     fprintf(stderr, "Invalid key (%s): must be a non-zero integer\n", argv[1]);
42,43c43,48
<   //outfileNAme is argv[2] + ".txt", so add 4 to its length.
<   char * outFileName = malloc((strlen(argv[2]) + 4) * sizeof(*outFileName));
---
>   char * outFileName = malloc((strlen(argv[2]) + 5) * sizeof(*outFileName));
>   if (outFileName == NULL) {
>     perror("Failed to allocate memory for output file name");
>     fclose(f);
>     return EXIT_FAILURE;
>   }
47c52,58
<   encrypt(f,key, outFile);
---
>   if (outFile == NULL) {
>     perror("Could not open output file");
>     free(outFileName);
>     fclose(f);
>     return EXIT_FAILURE;
>   }
>   encrypt(f, key, outFile);
49c60,62
<     perror("Failed to close the input file!");
---
>     perror("Failed to close the output file!");
>     free(outFileName);
>     fclose(f);
53a67
>     free(outFileName);
56c70
< 
---
>   free(outFileName);
[1m[7m%[27m[1m[0m                                                                                              ]7;file://atomxs-MBP.guests.lan/Users/atom.x/GitHub/Coding-practice/C-Duke/28_fix_vg_encr[0m[27m[24m[Jatom.x@atomxs-MBP 28_fix_vg_encr % [K[?2004h[?2004l
[1m[7m%[27m[1m[0m                                                                                              ]7;file://atomxs-MBP.guests.lan/Users/atom.x/GitHub/Coding-practice/C-Duke/28_fix_vg_encr[0m[27m[24m[Jatom.x@atomxs-MBP 28_fix_vg_encr % [K[?2004hdiff encrypt2.c encrypt1.c[?2004l
6,9c6,9
< void encrypt(FILE * f, int key, FILE * outfile){
<   char * line;
<   size_t sz;
<   while (getline(&line,&sz, f) >= 0) {
---
> void encrypt(FILE * f, int key, FILE * outfile) {
>   char * line = NULL;
>   size_t sz = 0;
>   while (getline(&line, &sz, f) != -1) {
14,18c14,18
< 	c = tolower(c);
< 	c -= 'a';
< 	c += key;
< 	c %= 26;
< 	c += 'a';
---
>         c = tolower(c);
>         c -= 'a';
>         c += key;
>         c %= 26;
>         c += 'a';
24a25
>   free(line);
29c30
<     fprintf(stderr,"Usage: encrypt key inputFileName\n");
---
>     fprintf(stderr, "Usage: encrypt key inputFileName\n");
34c35
<     fprintf(stderr,"Invalid key (%s): must be a non-zero integer\n", argv[1]);
---
>     fprintf(stderr, "Invalid key (%s): must be a non-zero integer\n", argv[1]);
42c43,48
<   char * outFileName = malloc((strlen(argv[2]) + 4) * sizeof(*outFileName));
---
>   char * outFileName = malloc((strlen(argv[2]) + 5) * sizeof(*outFileName));
>   if (outFileName == NULL) {
>     perror("Failed to allocate memory for output file name");
>     fclose(f);
>     return EXIT_FAILURE;
>   }
46c52,58
<   encrypt(f,key, outFile);
---
>   if (outFile == NULL) {
>     perror("Could not open output file");
>     free(outFileName);
>     fclose(f);
>     return EXIT_FAILURE;
>   }
>   encrypt(f, key, outFile);
48c60,62
<     perror("Failed to close the input file!");
---
>     perror("Failed to close the output file!");
>     free(outFileName);
>     fclose(f);
52a67
>     free(outFileName);
55c70
< 
---
>   free(outFileName);
[1m[7m%[27m[1m[0m                                                                                              ]7;file://atomxs-MBP.guests.lan/Users/atom.x/GitHub/Coding-practice/C-Duke/28_fix_vg_encr[0m[27m[24m[Jatom.x@atomxs-MBP 28_fix_vg_encr % [K[?2004h