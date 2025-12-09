#include <stdio.h>
#include <stdlib.h>

int my_strlen (char *string) {
    int length = 0;
    while(string[length] != '\0') {
        length++;
    }
    return length;
}

char* my_strcat (char *first_string, char *second_string) {
    int size1 = my_strlen(first_string);
    int size2 = my_strlen(second_string);
    int new_strlen = size1 + size2 + 1;
    char *new_str = (char *)malloc(new_strlen * sizeof(char));

    for (int i = 0; i < size1; i++) {
        new_str[i] = first_string[i];
    }

    for (int i = size1, j = 0; j < size2; i++, j++) {
        new_str[i] = second_string[j];
    }

    new_str[size1 + size2] = '\0';
    return new_str; // I have no idea why this works
}

int my_strcmp (char *first_string, char *second_string) {
    int size1 = my_strlen(first_string);
    int size2 = my_strlen(second_string);

    if (size1 != size2) {
        printf("Strings cannot be compared!");
        return 1;
    }
    for (int i = 0; i < size1; i++) {
        if (first_string[i] != second_string[i]) {
            return 1;
        }
    }
    return 0;
}

void my_strtok(char *string, char delim) {
    int i = 0;
    while(string[i] != '\0') {
        if(string[i] == delim) {
            printf("\n");
        } else {
            printf("%c", string[i]);
        }
        i++;
    }
}

int main() {
    return 0;
}