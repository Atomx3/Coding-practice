#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function is used to figure out the ordering
// of the strings in qsort. You do not need
// to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}

// This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

// This function reads lines from a file, sorts them, prints them, and frees memory.
void readAndSortFile(FILE *file) {
  char **lines = NULL;  // Array to hold lines of text
  size_t count = 0;     // Number of lines read
  size_t capacity = 0;  // Capacity of the lines array
  char *line = NULL;    // Buffer to hold each line
  size_t len = 0;       // Length of the buffer

  // Read lines from the file
  while (getline(&line, &len, file) != -1) {
    // If the array is full, double its capacity
    if (count == capacity) {
      capacity = capacity ? capacity * 2 : 1;
      lines = realloc(lines, capacity * sizeof(*lines));
      if (lines == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
      }
    }
    // Duplicate the line and store it in the array
    lines[count++] = strdup(line);
    if (lines[count - 1] == NULL) {
      perror("strdup");
      exit(EXIT_FAILURE);
    }
  }
  free(line);  // Free the buffer used by getline

  // Sort the lines
  sortData(lines, count);

  // Print the sorted lines
  for (size_t i = 0; i < count; i++) {
    printf("%s", lines[i]);
    free(lines[i]);  // Free each line after printing
  }
  free(lines);  // Free the array of lines
}

int main(int argc, char **argv) {
  // If no arguments are provided, read from standard input
  if (argc == 1) {
    readAndSortFile(stdin);
  } else {
    // Otherwise, read from each file provided as an argument
    for (int i = 1; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
      }
      readAndSortFile(file);
      fclose(file);
    }
  }
  return EXIT_SUCCESS;
}
