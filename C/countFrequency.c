#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char word[99];

    printf("Enter a word: ");
    scanf("%s", word);

    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }

    int count[99] = {0};
    int countLength = sizeof(count) / sizeof(count[0]);

    for (int i = 0; i < strlen(word); i++) {
        for (int j = 0; j <= i; j++) {
            if (word[i] == word[j]) {
                count[j]++;
            }
        }
    }

    int maxFrequency = count[0];
    int posOfMaxChar = 0;

    for (int k = 0; k < 3; k++) {
        if(count[k] > maxFrequency) {
            maxFrequency = count[k];
            posOfMaxChar = k;
        }
    }

    printf("Most occured character: %c, It's frequency: %d", posOfMaxChar + 'a', maxFrequency);
    return 0;
}

