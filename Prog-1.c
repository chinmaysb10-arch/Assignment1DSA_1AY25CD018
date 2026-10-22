
#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[20];
    float marks;
};

int main() {
    struct Student *ptr, *temp;
    int n, i, total;
    float sum = 0, average;
    char choice;

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    ptr = (struct Student *)malloc(n * sizeof(struct Student));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    total = n;

    /* Read student records */
    for (i = 0; i < total; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f",
              &(ptr + i)->roll_no,
              (ptr + i)->name,
              &(ptr + i)->marks);
    }

    /* Calculate average and find topper */
    sum = 0;
    int top = 0;

    for (i = 0; i < total; i++) {
        sum += (ptr + i)->marks;

        if ((ptr + i)->marks > (ptr + top)->marks) {
            top = i;
        }
    }

    average = sum / total;

    printf("\nAverage marks: %.2f\n", average);
    printf("Topper: %s (Roll %d, Marks %.2f)\n",
           (ptr + top)->name,
           (ptr + top)->roll_no,
           (ptr + top)->marks);

    /* Add two more students */
    printf("\nAdd 2 more students? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        temp = (struct Student *)realloc(
            ptr, (total + 2) * sizeof(struct Student));

        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            free(ptr);
            return 1;
        }

        ptr = temp;

        for (i = total; i < total + 2; i++) {
            printf("Enter roll, name, marks: ");
            scanf("%d %19s %f",
                  &(ptr + i)->roll_no,
                  (ptr + i)->name,
                  &(ptr + i)->marks);
        }

        total += 2;
        sum = 0;

        for (i = 0; i < total; i++) {
            sum += (ptr + i)->marks;
        }

        average = sum / total;

        printf("\nUpdated average marks: %.2f\n", average);
    }

    free(ptr);

    return 0;
}

