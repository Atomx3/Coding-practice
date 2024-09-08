#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

// Function to count the values in a file using key-value pairs
counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  // Open the input file for reading
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file");
    return NULL;
  }

  // Create a counts structure to store the counts
  counts_t * counts = createCounts();
  char * line = NULL;
  size_t sz = 0;

  // Read each line from the file
  while (getline(&line, &sz, f) >= 0) {
    // Remove newline character from the line
    line[strcspn(line, "\n")] = '\0';

    // Lookup the value corresponding to the key in the line
    char * value = lookupValue(kvPairs, line);

    // Add the count for the value (or <unknown> if not found)
    addCount(counts, value);
  }

  // Free the line buffer and close the file
  free(line);
  fclose(f);
  return counts;
}

int main(int argc, char ** argv) {
  // Check for the correct number of command-line arguments
  if (argc < 3) {
    fprintf(stderr, "Usage: %s kvfile inputfile1 [inputfile2 ...]\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Read the key/value pairs from the file named by argv[1]
  kvarray_t * kv = readKVs(argv[1]);
  if (kv == NULL) {
    fprintf(stderr, "Could not read key/value pairs from %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  // Loop through each input file from argv[2] to argv[argc-1]
  for (int i = 2; i < argc; i++) {
    // Count the values that appear in the file named by argv[i]
    counts_t * c = countFile(argv[i], kv);
    if (c == NULL) {
      fprintf(stderr, "Could not count values in %s\n", argv[i]);
      freeKVs(kv);
      return EXIT_FAILURE;
    }

    // Compute the output file name from argv[i]
    char * outName = computeOutputFileName(argv[i]);

    // Open the output file for writing
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      perror("Could not open output file");
      free(outName);
      freeCounts(c);
      freeKVs(kv);
      return EXIT_FAILURE;
    }

    // Print the counts to the output file
    printCounts(c, f);

    // Close the output file
    fclose(f);

    // Free the memory for outName and counts
    free(outName);
    freeCounts(c);
  }

  // Free the memory for the key/value pairs
  freeKVs(kv);
  return EXIT_SUCCESS;
}
