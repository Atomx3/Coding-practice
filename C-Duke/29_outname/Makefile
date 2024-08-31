# Compiler flags: 
# -Wall: enable all warnings
# -Werror: treat warnings as errors
# -std=gnu99: use the GNU99 standard
# -pedantic: enforce strict ISO C compliance
# -ggdb3: include debugging information
CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3

# Object files to be generated
OBJS=outname.o outname_test.o

# Name of the final executable program
PROGRAM=outname_test

# Rule to link the object files and create the executable
# $(PROGRAM) is outname_test, 
# $(OBJS) includes outname.o and outname_test.o
$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

# Pattern rule to compile .c files into .o files
# $<: the first prerequisite (the .c file)
%.o: %.c outname.h
	gcc -c $(CFLAGS) $<

# Rule to clean up the generated files
clean:
	rm -f $(OBJS) $(PROGRAM) *~




# Explanation:

# CFLAGS: These are the compiler flags used to compile the code with warnings, errors, standard compliance, and debugging information.
# OBJS: This variable lists the object files that need to be created.
# PROGRAM: This is the name of the final executable.
# Linking Rule: This rule links the object files ($(OBJS)) to create the executable ($(PROGRAM)).
# Pattern Rule: This rule compiles each .c file into a .o file. The %.o: %.c outname.h pattern means “for each .o file, compile the corresponding .c file and include outname.h”.
# Clean Rule: This rule removes the generated object files and the executable, as well as any backup files (*~).


# compiling process
# make
# ./outname_test
