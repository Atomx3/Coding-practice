#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

/**
 * Computes the output file name by appending ".counts" to the input file name.
 * 
 * @param inputName The name of the input file.
 * @return A dynamically allocated string containing the output file name.
 *         The caller is responsible for freeing this memory.
 */
char * computeOutputFileName(const char * inputName) {
    // Calculate the length of the input file name
    size_t len = strlen(inputName);
    
    // Allocate memory for the new file name (input length + ".counts" + null terminator)
    char * outputName = malloc((len + 8) * sizeof(*outputName)); // 7 for ".counts" + 1 for '\0'
    if (outputName == NULL) {
        // Return NULL if memory allocation fails
        return NULL;
    }
    
    // Copy the input file name to the newly allocated memory
    strcpy(outputName, inputName);
    
    // Append ".counts" to the input file name
    strcat(outputName, ".counts");
    
    // Return the new file name
    return outputName;
}
