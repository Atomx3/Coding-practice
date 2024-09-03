#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
// bath change the file name such as
// C programming practicing resources e698726c9a1d4750818a368764a8f78a.md
// C programming practicing resources.md
// because the downloaded files of Notion all include long name.

void renameFiles(const char *directory) {
    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) { // Only process regular files
            char oldName[256];
            char newName[256];
            snprintf(oldName, sizeof(oldName), "%s/%s", directory, entry->d_name);

            // Remove spaces and long strings from the file name
            char *token = strtok(entry->d_name, " ");
            char tempName[256] = "";
            while (token != NULL) {
                if (strlen(token) <= 20) {
                    strcat(tempName, token);
                }
                token = strtok(NULL, " ");
            }

            // Get the file extension
            char *ext = strrchr(entry->d_name, '.');
            if (ext != NULL) {
                strcat(tempName, ext); // Keep the original extension
            }

            // Create the new file name
            snprintf(newName, sizeof(newName), "%s/%s", directory, tempName);

            // Rename the file
            if (rename(oldName, newName) != 0) {
                perror("rename");
            } else {
                printf("Renamed: %s -> %s\n", oldName, newName);
            }
        }
    }

    closedir(dp);
}

int main() {
    const char *directory = "."; // Use current directory

    renameFiles(directory);

    return 0;
}
