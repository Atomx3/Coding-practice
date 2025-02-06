1. Make sure you have saved the changes to your file and recompiled it:

``` gcc -g -o outOfBounds outOfBounds.c ```

2. Then, run Valgrind and GDB again:

Run Valgrind with GDB in the first terminal:
``` valgrind --vgdb=yes --vgdb-error=0 ./outOfBounds ```

3. Open a new terminal and start GDB:
``` (gdb) ./outOfBounds ```

4. Connect GDB to Valgrind in the GDB terminal:
``` target remote | /usr/local/Cellar/valgrind/HEAD-93191c1/libexec/valgrind/../../bin/vgdb --pid=<pid> ```

5. Run the leak checker in GDB:
(gdb) monitor leak_check full reachable any

If you still see the message indicating no leaks, it might be helpful to ensure that the program is indeed running the version with the leaks. You can add some print statements to verify that the correct code is being executed.


