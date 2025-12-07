#include <stdio.h>
#include <string.h>

int calc(int firstNum, int secondNum, char operator[]);

int main() {
    int a, b, result;
    char opr[16];

    printf("Enter two numbers: ");
    int inputResult = scanf("%d %d", &a, &b);
    if (inputResult != 2) {
        printf("please only enter numbers!");
        return 1;
    } 
    printf("Enter the operation to perform: ");
    scanf("%s", opr);

    if ((strcmp(opr, "add") != 0) && 
        (strcmp(opr, "subtract") != 0) && 
        (strcmp(opr, "multiply") != 0) && 
        (strcmp(opr, "divide") != 0)) {
        printf("Enter a valid operation!");
        return 1;
    } else if (b == 0 && (strcmp(opr, "divide") == 0)) {
        printf("Division by 0 is not possible!");
        return 1;
    } else {
        result = calc(a, b, opr);
        printf("%d", result);
        return 0;
    }
}

int calc(int firstNum, int secondNum, char operator[]) {
    if (strcmp(operator, "add") == 0) {
        return firstNum + secondNum;
    }
    if (strcmp(operator, "subtract") == 0) {
        return firstNum - secondNum;
    }
    if (strcmp(operator, "multiply") == 0) {
        return firstNum * secondNum;
    }
    if (strcmp(operator, "divide") == 0) {
        return firstNum / secondNum;
    }
}


