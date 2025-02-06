#include <stdio.h>
#include <stdlib.h>

// Interacting with the System and Managing Memory, Duke University
// coursera, Module 2, lesson 6 Valgrind

int main() {
    printf("Starting the program\n");
    int *ptr = (int *)malloc(4 * sizeof(int)); // Allocate memory for 4 integers

    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("Memory allocated for ptr\n");

    // Memory leak: allocated memory not freed
    int *leak1 = (int *)malloc(4 * sizeof(int));
    int *leak2 = (int *)malloc(4 * sizeof(int));
    printf("Memory allocated for leak1 and leak2\n");

    // Use the allocated memory
    for (int i = 0; i < 4; i++) {
        ptr[i] = i;
    }
    printf("Memory used for ptr\n");

    // Intentionally not freeing leak1 and leak2 to create memory leaks
    // free(leak1);
    // free(leak2);

    free(ptr); // Free the allocated memory
    printf("Memory freed for ptr\n");

    return 0;
}
