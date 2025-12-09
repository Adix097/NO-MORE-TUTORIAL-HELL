#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int marks;
} Student;

int main() {
    Student students[100];
    int student_count = 0;
    char buffer[1000];
    char *name, *marks;

    FILE *student_data = fopen("data.csv", "r");
    if (student_data == NULL) {
        printf("FILE DID NOT OPEN!!");
        return 1;
    }

    fgets(buffer, sizeof(buffer), student_data);
    while(fgets(buffer, sizeof(buffer), student_data)) {
        name = strtok(buffer, ",");
        marks = strtok(NULL, ",");
        
        if (!name || !marks) continue;

        strcpy(students[student_count].name, name);
        students[student_count].marks = atoi(marks);
        student_count++;
    }

    // finding maximum marks
    int max_marks = students[0].marks;
    char top_student[50];
    strcpy(top_student, students[0].name);
    for (int i = 0; i < student_count; i++) {
        if (max_marks < students[i].marks) {
            strcpy(top_student, students[i].name);
            max_marks = students[i].marks;
        }
    }

    // finding mean
    int mean, sum = 0;
    for (int i = 0; i < student_count; i++) {
        sum += students[i].marks;
        mean = sum / student_count;
    }

    printf("Mean of marks obtained by all the students is %d.\n", mean);
    printf("%s achieved the highest score of %d.", top_student, max_marks);
    return 0;
}