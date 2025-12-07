#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void appendMarks(float **studentMarks, int *count, int *capacity, float *valueToAdd) {
    if (*count >= *capacity) {
        (*capacity) *= 2;
        *studentMarks = realloc(*studentMarks, *capacity * sizeof(float));
    }
    (*studentMarks)[*count] = *valueToAdd;
    (*count)++;
}

int popElement(float **studentMarks, int *count, int *capacity, int *indexToPop) {
    if ((*indexToPop) >= *count || (*indexToPop) < 0) { 
        printf("Not a valid index!");
        return 1;
    } else {
        for (int i = (*indexToPop); i < *count - 1; i++) {
            (*studentMarks)[i] = (*studentMarks)[i + 1];
        }

        (*count)--;

        if (*count <= *capacity / 4 && *capacity > 1) {
            *capacity /= 2;
            *studentMarks = realloc(*studentMarks, *capacity * sizeof(float));
        }
        return 0;
    }
}

int editElement(float **studentMarks, int *count, int *capacity, int *indexToEdit, float *newValue) {
    if ((*indexToEdit) >= *count || (*indexToEdit) < 0) { 
        printf("Not a valid index!");
        return 1;
    } else {
        (*studentMarks)[*indexToEdit] = (*newValue);
        return 0;
    }
}

int main() {
    int count = 0; // how many marks currently stored
    int capacity = 1; // how many marks can be stored before re-sizing
    int status = 0; //  0 = success, 1 = failure
    float *studentMarks = (float *)malloc(capacity * sizeof(float));

    // starting menu
    char operation[64];
    printf("\n-------Welcome to student marks management system-------\n");
    printf("Enter the operation you want to perform (add/edit/delete/print/average): ");
    scanf("%s", &operation);

    if (strcmp(operation, "add") != 0 &&
        strcmp(operation, "edit") != 0 &&
        strcmp(operation, "delete") != 0 &&
        strcmp(operation, "print") != 0 &&
        strcmp(operation, "average") != 0) {
            printf("Please enter a valid operation");
            status = 1;
            goto cleanup;
        } else {
            // to add new student
            if (strcmp(operation, "add") == 0) {
                float valueToAdd = 0;
                printf("Enter marks: ");
                scanf("%f", &valueToAdd);
                appendMarks(&studentMarks, &count, &capacity, &valueToAdd);
                printf("Student is successfully added!");
            }

            // to delete element
            if (strcmp(operation, "delete") == 0) {
                if (count == 0) {
                    printf("No student available!");
                    status = 1;
                    goto cleanup;
                } else {
                    int indexToPop;
                    printf("Enter position to delete (current number of students is %d): ", count);
                    scanf("%d", &indexToPop);
                    indexToPop--;
                    int popResult = popElement(&studentMarks, &count, &capacity, &indexToPop);
                    if (popResult == 0) {
                        printf("Student is successfully removed!");
                    } else {
                        status = 1;
                        goto cleanup;
                    }
                }
            }


            // to edit
            if (strcmp(operation, "edit") == 0) {
                if (count == 0) {
                    printf("No student available!");
                    status = 1;
                    goto cleanup;
                } else {
                    int indextoEdit;
                    float newValue = 0;
                    printf("Enter position to edit (current number of students is %d): ", count);
                    scanf("%d", &indextoEdit);
                    indextoEdit--;

                    printf("Enter new value (Original value was %.2f): ", studentMarks[indextoEdit]);
                    scanf("%f", &newValue);

                    int editResult = editElement(&studentMarks, &count, &capacity, &indextoEdit, &newValue);
                    if (editResult == 0) {
                        printf("Student is successfully edited!");
                    } else {
                        status = 1;
                        goto cleanup;
                    }
                }
            }

            // to print
            if (strcmp(operation, "print") == 0) {
                if (count == 0) {
                    printf("No student available!");
                    status = 1;
                    goto cleanup;
                } else {
                    printf("Here is the list of marks obtained by students:\n");
                    for (int i = 0; i < count; i++) {
                        printf("%.1f\n", studentMarks[i]);
                    }
                }
            }

            // to print the average
            if(strcmp(operation, "average") == 0) {
                float sum = 0;
                for(int i = 0; i < count; i++) {
                    sum += studentMarks[i];
                }
                printf("Average of students is %.2f.", sum/count);
            }

        }
    
    cleanup:
        free(studentMarks);
        return status;
}

