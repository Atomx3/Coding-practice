#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>
#include <wchar.h>
#include <locale.h>
// batch change the file name such as
// C programming practicing resources e698726c9a1d4750818a368764a8f78a.md
// C programming practicing resources.md
// some of ramdonizer create such kind of long name.

void renameFiles(const char *directory) {
    setlocale(LC_ALL, "");

    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) {
            char oldName[256];
            snprintf(oldName, sizeof(oldName), "%s/%s", directory, entry->d_name);

            char baseNameCopy[256];
            strcpy(baseNameCopy, entry->d_name);

            char *baseName = basename(baseNameCopy);
            char *ext = strrchr(baseName, '.');
            char extStr[256] = "";
            if (ext != NULL) {
                strcpy(extStr, ext);
                *ext = '\0';
            } else {
                continue; // Skip files without extensions
            }

            char *lastSpace = strrchr(baseName, ' ');
            if (lastSpace != NULL) {
                char tempName[256];
                strncpy(tempName, baseName, lastSpace - baseName); // Copy up to the last space
                tempName[lastSpace - baseName] = '\0'; // Null-terminate
                strcat(tempName, extStr); // Add the extension back

                char newName[256];
                snprintf(newName, sizeof(newName), "%s/%s", directory, tempName);

                if (rename(oldName, newName) != 0) {
                    wprintf(L"Rename failed: %ls -> %ls\n", oldName, newName);
                } else {
                    wprintf(L"Renamed: %ls -> %ls\n", oldName, newName);
                }
            } // else: filename doesn't have the space and long code, so skip
        }
    }

    closedir(dp);
}

int main() {
    const char *directory = ".";
    renameFiles(directory);
    return 0;
}
