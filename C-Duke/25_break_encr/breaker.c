#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26 // Define the size of the alphabet

// Function to perform frequency analysis on the text
void frequencyAnalysis(FILE *file, int *freq) {
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) { // Check if the character is a letter
            c = tolower(c); // Convert the letter to lowercase
            freq[c - 'a']++; // Increment the frequency count for the letter
        }
    }
}

// Function to find the index of the most frequent letter
int findMaxFrequencyIndex(int *freq) {
    int maxIndex = 0;
    for (int i = 1; i < ALPHABET_SIZE; ++i) {
        if (freq[i] > freq[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "error, please input: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    int freq[ALPHABET_SIZE] = {0};

    frequencyAnalysis(file, freq); // Perform frequency analysis on the text
    int maxFreqIndex = findMaxFrequencyIndex(freq); // Find the most frequent letter
    int shift = (maxFreqIndex + 22) % ALPHABET_SIZE; // Calculate the shift

    if (shift < 0 || shift >= ALPHABET_SIZE) {
        fprintf(stderr, "Error: encryption key out of range\n");
        fclose(file);
        return EXIT_FAILURE;
    } else {
        fprintf(stdout, "%d\n", shift); // Print the decryption key
    }

    //decryptCaesarCipher(text, shift); // Decrypt the text
    //printf("Decrypted message: %s\n", text); // Print the decrypted message

    if (fclose(file) != 0) {
        perror("Failed to close the input file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/*

// Function to decrypt the Caesar cipher
void decryptCaesarCipher(char *text, int shift) {
    int i;
    char ch;
    for (i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        if (isalpha(ch)) { // Check if the character is a letter
            if (islower(ch)) { // Handle lowercase letters
                ch = ch - shift;
                if (ch < 'a') {
                    ch = ch + 'z' - 'a' + 1;
                }
            } else if (isupper(ch)) { // Handle uppercase letters
                ch = ch - shift;
                if (ch < 'A') {
                    ch = ch + 'Z' - 'A' + 1;
                }
            }
            text[i] = ch; // Update the character in the text
        }
    }
}

int main() {
    
    char text[1000];
    int freq[ALPHABET_SIZE] = {0};

    size_t bytesRead = fread(text, sizeof(char), sizeof(text) - 1, file);
    if (bytesRead == 0 && !feof(file)) {
        fprintf(stderr, "Error reading file %s\n", argv[1]);
        fclose(file);
        return EXIT_FAILURE;
    }
    text[bytesRead] = '\0'; // Null-terminate the string

    if (bytesRead == 0) {
        fprintf(stderr, "Error: file %s is empty\n", argv[1]);
        fclose(file);
        return EXIT_FAILURE;
    }


    decryptCaesarCipher(text, shift); // Decrypt the text
    printf("Decrypted message: %s\n", text); // Print the decrypted message


}
*/
