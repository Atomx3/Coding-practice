#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// original code, add commets for the parts will be modified.

void encrypt(FILE * f, int key, FILE * outfile){
  // Initialization of line and sz ?
  char * line;
  size_t sz;
  // Condition in getline ?
  while (getline(&line,&sz, f) >= 0) {
    char * ptr = line;
    while (*ptr != '\0') {
      int c = *ptr;
      if (isalpha(c)) {
	c = tolower(c);
	c -= 'a';
	c += key;
	c %= 26;
	c += 'a';
      }
      *ptr = c;
      ptr++;
    }
    fprintf(outfile, "%s", line);
  }
  // Added free(line); at the end of the encrypt function ?
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr,"Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  int key = atoi(argv[1]);
  if (key == 0) {
    fprintf(stderr,"Invalid key (%s): must be a non-zero integer\n", argv[1]);
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[2], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  //outfileNAme is argv[2] + ".txt", so add 4 to its length.
  // Output File Name Allocation ?
  char * outFileName = malloc((strlen(argv[2]) + 4) * sizeof(*outFileName));
  // Error Handling for Memory Allocation ?

  strcpy(outFileName, argv[2]);
  strcat(outFileName, ".enc");
  FILE * outFile = fopen(outFileName, "w");
  // Error Handling for Output File Opening ?

  encrypt(f,key, outFile);
  if (fclose(outFile) != 0) {
    perror("Failed to close the input file!");
    // Freeing outFileName ?
    return EXIT_FAILURE;
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    // Freeing outFileName ?
    return EXIT_FAILURE;
  }
  // Added free(outFileName); after closing files.
  return EXIT_SUCCESS;
}
