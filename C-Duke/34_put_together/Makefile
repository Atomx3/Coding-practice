# Compiler flags for warnings, errors, and debugging
CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3

# List all source files except main-source.c
# main_source.c is duplicated of main.c as backup
SRCS=$(filter-out main-source.c, $(wildcard *.c))

# Convert source files to object files
OBJS=$(patsubst %.c, %.o, $(SRCS))

# Name of the final executable program
PROGRAM=count_values

# Rule to link object files into the final executable
$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

# Rule to compile source files into object files
%.o: %.c 
	gcc -c $(CFLAGS) $<

# Rule to clean up the directory by removing object files and the executable
clean:
	rm -f $(OBJS) $(PROGRAM) *~

# Dependencies for object files
counts.o: counts.h
outname.o: outname.h
kv.o: kv.h
main.o: kv.h
main.o: outname.h
main.o: counts.h
