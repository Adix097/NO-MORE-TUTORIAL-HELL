#include <stdio.h>
#include <string.h>

int main() {
    int status = 0; // 0 = success, 1 = failure
    char userdata[256];
    char filename[16];
    char copiedFilename[64];
    
    printf("Write something (press enter when finished): ");
    scanf("%s", userdata);

    if (userdata[0] == '\n') {
        printf("Nothing is typed!");
        status = 1;
        goto end;
    }

    char isSave;
    int saveStatus = 1;
    printf("Do you want save it (y/n): ");
    scanf(" %c", &isSave);

    if (isSave == 'y') {
        printf("Write the name of the file: ");
        scanf("%s", filename);
        strcat(filename, ".txt");
        FILE *fuser = NULL;
        fuser = fopen(filename, "w");
        if (fuser == NULL) {
            printf("File cannot be created!");
            status = 1;
            goto end;
        }
        fputs(userdata, fuser);
        printf("File created successfully!");
        fclose(fuser);

        // creating a copy
        char isCopy;
        printf("Do you want to copy this file to another file (y/n):");
        scanf(" %c", &isCopy);
        if (isCopy == 'y') {
            char buffer[256];
            char filedata[256];
            sprintf(copiedFilename, "copyof%s", filename);

            FILE *src = fopen(filename, "r"); // file saved by user
            FILE *fcopy = fopen(copiedFilename, "w");

            if (!src || !fcopy) {
                printf("Copy failed!");
                if (src) fclose(src);
                if (fcopy) fclose(fcopy);
                status = 1;
                goto end;
            }

            while (fgets(buffer, sizeof(buffer), src)) {
                fputs(buffer, fcopy);
            }
            printf("File copied successfully!");
            fclose(src);
            fclose(fcopy);
        }
    } else {
        printf("Your data is deleted nothing got saved: ");
    }

    end:
        return status;
}