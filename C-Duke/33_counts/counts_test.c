#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

#define NUM_TESTS 12

int main(void) {
  // Test data with some names and NULL values
  char * testData[NUM_TESTS] = {"apple", "banana", NULL, "apple",
                                "frog", "sword", "bear", NULL,
                                "frog", "apple", "zebra", "knight"};
  
  // Create a counts_t structure
  counts_t * testCounts = createCounts();
  
  // Add counts for each name in the test data
  for (int i = 0; i < NUM_TESTS; i++) {
    addCount(testCounts, testData[i]);
  }
  
  // Print the counts to stdout
  printCounts(testCounts, stdout);
  
  // Free the memory associated with the counts_t structure
  freeCounts(testCounts);
  
  return EXIT_SUCCESS;
}
