# Valgrind-memcheck

please check program memcheck.c

https://valgrind.org


## error report 1
Heap Block Overrun: The line x[10] = 0; is trying to write to the 11th element of the array x, which only has 10 elements (indices 0 to 9). This causes an invalid write.
Memory Leak: The allocated memory for x is not freed before the function f returns, 
causing a memory leak.

```% gcc -g -o memcheck memcheck.c ```
``` % valgrind --leak-check=full --track-origins=yes ./memcheck ```

``
==27535== Memcheck, a memory error detector
==27535== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==27535== Using Valgrind-3.23.0.GIT-lbmacos and LibVEX; rerun with -h for copyright info
==27535== Command: ./memcheck
==27535==
// program writes 4 bytes to a memory location that it can’t access.
==27535== Invalid write of size 4
==27535==    at 0x100003F5A: ??? (in ./memcheck)
==27535==    by 0x100003F83: ??? (in ./memcheck)
==27535==    by 0x10001551D: (below main) (in /usr/lib/dyld)
// After a memory block of size 40 bytes, invalid write is happening.
// which was allocated using malloc.
// 0x100223cb8 is the address where the invalid write occurred, 
// which is right after the allocated block of size 40 bytes.
==27535==  Address 0x100223cb8 is 0 bytes after a block of size 40 alloc'd
==27535==    at 0x1001EDFBB: malloc (in /usr/local/Cellar/
	valgrind/HEAD-93191c1/libexec/valgrind/vgpreload_memcheck
	-amd64-darwin.so)
==27535==    by 0x100003F51: ??? (in ./memcheck)
==27535==    by 0x100003F83: ??? (in ./memcheck)
==27535==    by 0x10001551D: (below main) (in /usr/lib/dyld)
``


## // error reports 2
Ensure you access only valid indices of the allocated array.

the leak is occurring within the system libraries 
(libobjc.A.dylib) rather than your own code
```% valgrind --leak-check=full --track-origins=yes ./memcheck```

``
==28033== Memcheck, a memory error detector
==28033== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==28033== Using Valgrind-3.23.0.GIT-lbmacos and LibVEX; rerun with -h for copyright info
==28033== Command: ./memcheck
==28033== // 28033 is a process identifier(PID) that Valgrind assigns
==28033== // to the instance of your program being analyzed.

// an overview of memory usage
==28033== HEAP SUMMARY: 
==28033==     in use at exit: 8,411 bytes in 168 blocks
==28033==   total heap usage: 172 allocs, 4 frees, 8,523 bytes allocated
==28033==
// Call Stack: The call stack shows that the leak 
// is occurring within the libobjc.A.dylib library, 
// specifically in the realizeClassWithoutSwift function.
==28033== 32 bytes in 1 blocks are definitely lost in loss record 8 of 28
==28033==    at 0x1001F224C: calloc (in /usr/local/Cellar/valgrind/HEAD-93191c1/libexec/valgrind/vgpreload_memcheck-amd64-darwin.so)
==28033==    by 0x7FF804DE084F: realizeClassWithoutSwift(objc_class*, objc_class*) (in /usr/lib/libobjc.A.dylib)
==28033==    by 0x7FF804DE08F8: realizeClassWithoutSwift(objc_class*, objc_class*) (in /usr/lib/libobjc.A.dylib)
==28033==    by 0x7FF804DE08F8: realizeClassWithoutSwift(objc_class*, objc_class*) (in /usr/lib/libobjc.A.dylib)
==28033==    by 0x7FF804DDEB59: map_images_nolock (in /usr/lib/libobjc.A.dylib)
==28033==    by 0x7FF804DDD4DB: map_images (in /usr/lib/libobjc.A.dylib)
==28033==    by 0x10001F2CA: invocation function for block 
	in dyld4::RuntimeState::setObjCNotifiers(void (*)(unsigned int, 
	char const* const*, mach_header const* const*), void (*)
	(char const*, mach_header const*), void (*)(char const*, 
	mach_header const*)) (in /usr/lib/dyld)
``

/* Ignore System Library Leaks: 
If the memory leak is within system libraries and not your code, 
you can generally ignore these leaks. 
They are often outside your control and may not impact your 
application’s performance significantly.行·
*/


## Uninitialized Values
run Valgrind, it will report where the uninitialized value was created.
```valgrind --track-origins=yes ./myProgram```

``
==12260== Conditional jump or move depends on uninitialised value(s)
==12260==    at 0x4E8158E: vfprintf (vfprintf.c:1660)
==12260==    by 0x4E8B498: printf (printf.c:33)
==12260==    by 0x400556: f (uninit.c:7)
==12260==    by 0x400580: main (uninit.c:15)
==12260==  Uninitialised value was created by a stack allocation
==12260==    at 0x40052D: f (uninit.c:4)
``

## Valgrind + GDB 
``` gcc -g -o my_program my_program.c ("memcheck" in current program)```

``` valgrind --vgdb=full --vgdb-error=0 ./my_program ```

output as below

``
==1065== Memcheck, a memory error detector
==1065== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==1065== Using Valgrind-3.23.0.GIT-lbmacos and LibVEX; rerun with -h for copyright info
==1065== Command: ./memcheck
==1065==
==1065== (action at startup) vgdb me ...
==1065==
==1065== TO DEBUG THIS PROCESS USING GDB: start GDB like this
==1065==   /path/to/gdb ./memcheck
==1065== and then give GDB the following command
==1065==   target remote | /usr/local/Cellar/valgrind/HEAD-93191c1/libexec/valgrind/../../bin/vgdb --pid=1065
==1065== --pid is optional if only one valgrind process is running
==1065==

``

## GDB 

open another terminal and input command line.

``` gdb ./my_program ```

``
GNU gdb (GDB) 15.1
Copyright (C) 2024 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-apple-darwin21.6.0".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./memcheck...
Reading symbols from /Users/atom.x/GitHub/test/memcheck.dSYM/Contents/Resources/DWARF/memcheck...
(gdb) 
``

```
(gdb) target remote | /usr/local/Cellar/valgrind/HEAD-93191c1/libexec/valgrind/../../bin/vgdb --pid=1065
```

``
Remote debugging using | /usr/local/Cellar/valgrind/HEAD-93191c1/libexec/valgrind/../../bin/vgdb --pid=1065
relaying data between gdb and process 1065
0x0000000100014ad0 in ?? ()
``

```(gdb) continue ```

``
Continuing.

Program received signal SIGTRAP, Trace/breakpoint trap.

0x0000000100003f5a in f () at memcheck.c:8

``

```
8	     x[10] = 0;        // problem 1: heap block overrun
(gdb) list
3	
4	// error reports, by below section of code
5	  void f(void)
6	  {
7	     int* x = malloc(10 * sizeof(int));
8	     x[10] = 0;        // problem 1: heap block overrun
9	  }                    // problem 2: memory leak -- x not freed
10	
11	
12	// fix the above problem
```

``` (gdb) print x ```

``
$1 = (int *) 0x100223c90
``

```(gdb) backtrace```

``
#0  0x0000000100003f5a in f () at memcheck.c:8

#1  0x0000000100003f84 in main () at memcheck.c:24

``

``` (gdb) next ```

``
9	  }                    // problem 2: memory leak -- x not freed
``

```(gdb) step```

``
main () at memcheck.c:25
25	     return 0;
``

``` (gdb) continue ```

``` (gdb) monitor who_points_at 0x51fc040(eg. memory location) ```


## install GDB

``` brew install gdb ```
 
Code Signing in the Keychain Access application of Macbook pro.

Configure GDB

``` echo "set startup-with-shell off" >> ~/.gdbinit ```

