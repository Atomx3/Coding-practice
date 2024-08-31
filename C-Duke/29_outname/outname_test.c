#include "outname.h"
#include <stdio.h>
#include <stdlib.h>

/* 
#define: a preprocessor directive in C that defines a constant. 
NUM_TESTS: the constant.
3: The value assigned to the constant.
anywhere NUM_TESTS appears in your code, 
it will be replaced with 3 by the preprocessor before compilation.
 */
#define NUM_TESTS 3

/**
 * Main function to test the computeOutputFileName function.
 * It runs several test cases and prints the results.
 */
int main(void) {
  // Array of test input file names
  char * testNames[NUM_TESTS] = {
    "input.txt",
    "anotherTestFileName.txt",
    "somethingelse"};

  // Loop through each test case
  for (int i = 0; i < NUM_TESTS; i++) {
    // Compute the output file name for the current test case
    char * outName = computeOutputFileName(testNames[i]);
    
    // Print the input and corresponding output file names
    printf("'%s' => '%s'\n", testNames[i], outName);
    
    // Free the allocated memory for the output file name
    free(outName);
  }
  
  // Return success status
  return EXIT_SUCCESS;
}
