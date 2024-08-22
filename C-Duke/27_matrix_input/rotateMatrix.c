#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to rotate the matrix 90 degrees clockwise
void rotate(char matrix[10][10]) {
    char matrixN[10][10];

    // Copy the rotated values into a new matrix
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            matrixN[i][j] = matrix[9 - j][i];
        }
    }

    // Copy the new matrix back into the original matrix
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            matrix[i][j] = matrixN[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if the correct number of command line arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open the input file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char matrix[10][10];
    char line[12]; // 10 characters + newline + null terminator

    // Read the matrix from the file
    for (int i = 0; i < 10; ++i) {
        if (!fgets(line, sizeof(line), file)) {
            fprintf(stderr, "Error reading line %d\n", i + 1);
            fclose(file);
            return EXIT_FAILURE;
        }

        // Check if the line has exactly 10 characters followed by a newline
        if (strchr(line, '\n') == NULL || strlen(line) != 11) {
            fprintf(stderr, "Invalid line length at line %d\n", i + 1);
            fclose(file);
            return EXIT_FAILURE;
        }

        // Copy the line into the matrix
        strncpy(matrix[i], line, 10);
    }

    // Check if there are more lines in the file
    if (fgets(line, sizeof(line), file)) {
        fprintf(stderr, "Error: Input file contains more than 10 lines\n");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    // Close the input file
    fclose(file);

    // Rotate the matrix
    rotate(matrix);

    // Print the rotated matrix to stdout
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            putchar(matrix[i][j]);
        }
        putchar('\n');
    }

    return EXIT_SUCCESS;
}

