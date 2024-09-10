#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
// ../34_put_together, symbolink to ../33_counts/
// Function to create and initialize a counts_t structure
counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  counts->counts = NULL;
  counts->size = 0;
  counts->unknown_count = 0;
  return counts;
}

// Function to add a count for a given name
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknown_count++;
    return;
  }
  // Check if the name already exists in the counts array
  for (size_t i = 0; i < c->size; i++) {
    if (strcmp(c->counts[i].name, name) == 0) {
      c->counts[i].count++;
      return;
    }
  }
  // If the name does not exist, add it to the array
  c->counts = realloc(c->counts, (c->size + 1) * sizeof(*c->counts));
  c->counts[c->size].name = strdup(name);
  c->counts[c->size].count = 1;
  c->size++;
}

// Function to print the counts to a file
void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->counts[i].name, c->counts[i].count);
  }
  if (c->unknown_count > 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->unknown_count);
  }
}

// Function to free all memory associated with a counts_t structure
void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->size; i++) {
    free(c->counts[i].name);
  }
  free(c->counts);
  free(c);
}
