#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// modified program with comments, now it runs well.

// Function to encrypt the contents of a file
void encrypt_file(FILE * f, int key, FILE * outfile) {
  char * line = NULL; // Pointer to hold each line read from the file
  size_t sz = 0; // Variable to hold the size of the buffer

  // Read each line from the input file
  while (getline(&line, &sz, f) != -1) {
    char * ptr = line; // Pointer to traverse the line

    // Encrypt each character in the line
    while (*ptr != '\0') {
      int c = *ptr;
      if (isalpha(c)) { // Check if the character is an alphabet
        c = tolower(c); // Convert to lowercase
        c -= 'a'; // Shift to 0-based index
        c += key; // Apply the encryption key
        c %= 26; // Wrap around within the alphabet
        c += 'a'; // Shift back to ASCII value
      }
      *ptr = c; // Update the character in the line
      ptr++; // Move to the next character
    }
    fprintf(outfile, "%s", line); // Write the encrypted line to the output file
  }
  free(line); // Free the allocated memory for the line
}

int main(int argc, char ** argv) {
  if (argc != 3) { // Check if the correct number of arguments is provided
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }

  int key = atoi(argv[1]); // Convert the key argument to an integer
  if (key == 0) { // Check if the key is valid
    fprintf(stderr, "Invalid key (%s): must be a non-zero integer\n", argv[1]);
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[2], "r"); // Open the input file for reading
  if (f == NULL) { // Check if the file was opened successfully
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  // Allocate memory for the output file name
  char * outFileName = malloc((strlen(argv[2]) + 5) * sizeof(*outFileName));
  if (outFileName == NULL) { // Check if memory allocation was successful
    perror("Failed to allocate memory for output file name");
    fclose(f);
    return EXIT_FAILURE;
  }

  // Create the output file name by appending ".enc" to the input file name
  strcpy(outFileName, argv[2]);
  strcat(outFileName, ".enc");

  FILE * outFile = fopen(outFileName, "w"); // Open the output file for writing
  if (outFile == NULL) { // Check if the file was opened successfully
    perror("Could not open output file");
    free(outFileName);
    fclose(f);
    return EXIT_FAILURE;
  }

  encrypt_file(f, key, outFile); // Encrypt the contents of the input file and write to the output file

  // Close the output file and check for errors
  if (fclose(outFile) != 0) {
    perror("Failed to close the output file!");
    free(outFileName);
    fclose(f);
    return EXIT_FAILURE;
  }

  // Close the input file and check for errors
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    free(outFileName);
    return EXIT_FAILURE;
  }

  free(outFileName); // Free the allocated memory for the output file name
  return EXIT_SUCCESS; // Indicate successful completion
}
