#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

// Helper function to split a line into key and value
kvpair_t parseKV(const char * line) {
  kvpair_t pair;
  // Find the first '=' character in the line
  char *delimiter = strchr(line, '=');
  if (delimiter == NULL) {
    fprintf(stderr, "Invalid line: %s\n", line);
    exit(EXIT_FAILURE);
  }
  // Calculate the length of the key
  size_t key_len = delimiter - line;
  // Allocate memory and copy the key part of the line
  pair.key = strndup(line, key_len);
  // Allocate memory and copy the value part of the line
  pair.value = strdup(delimiter + 1);

  // Remove newline character from value if present
  char *newline = strchr(pair.value, '\n');
  if (newline != NULL) {
    *newline = '\0';
  }

  return pair;
}

kvarray_t * readKVs(const char * fname) {
  // Open the file for reading
  FILE *f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    return NULL;
  }

  // Allocate memory for the kvarray_t structure
  kvarray_t *kvArray = malloc(sizeof(*kvArray));
  kvArray->pairs = NULL;
  kvArray->length = 0;

  char *line = NULL;
  size_t sz = 0;
  // Read each line from the file
  while (getline(&line, &sz, f) != -1) {
    // Reallocate memory to accommodate the new key/value pair
    kvArray->pairs = realloc(kvArray->pairs, (kvArray->length + 1) * sizeof(*kvArray->pairs));
    // Parse the line into a key/value pair and add it to the array
    kvArray->pairs[kvArray->length] = parseKV(line);
    kvArray->length++;
  }
  free(line);
  fclose(f);
  return kvArray;
}

void freeKVs(kvarray_t * pairs) {
  // Free each key and value in the array
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->pairs[i].key);
    free(pairs->pairs[i].value);
  }
  // Free the array of pairs and the kvarray_t structure itself
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  // Print each key/value pair in the array
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  // Search for the key in the array
  for (size_t i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->pairs[i].key, key) == 0) {
      // Return the corresponding value if the key is found
      return pairs->pairs[i].value;
    }
  }
  // Return NULL if the key is not found
  return NULL;
}
