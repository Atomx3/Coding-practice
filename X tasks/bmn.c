/*
Batch modify name
批量修改文件名

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void renameFiles(const char *directory, const char *newRoomName) {
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

            // Extract date and time from the old file name
            char date[11], time[9];
            sscanf(entry->d_name, "%10s %8s", date, time);

            // Create the new file name
            snprintf(newName, sizeof(newName), "%s/%s %s %s", directory, date, time, newRoomName);

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
    const char *directory = "./files"; // Directory containing the files
    const char *newRoomName = "HOXDAO 280250508"; // New room name

    renameFiles(directory, newRoomName);

    return 0;
}
