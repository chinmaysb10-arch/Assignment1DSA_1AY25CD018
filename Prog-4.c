
#include <stdio.h>

#define MAX 100

typedef struct {
    int row, col, value;
} term;

void fast_transpose(term a[], term b[])
{
    int row_terms[MAX], starting_pos[MAX];
    int next_pos[MAX];
    int i, j, num_cols, num_terms;

    num_cols = a[0].col;
    num_terms = a[0].value;

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;

    /* Count terms in each column */
    for (i = 0; i < num_cols; i++)
        row_terms[i] = 0;

    for (i = 1; i <= num_terms; i++)
        row_terms[a[i].col]++;

    /* Calculate starting positions */
    starting_pos[0] = 1;

    for (i = 1; i < num_cols; i++)
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];

    /* Print arrays before positions are updated */
    printf("\nrow_terms[]:\n");
    for (i = 0; i < num_cols; i++)
        printf("%d ", row_terms[i]);

    printf("\nstarting_pos[]:\n");
    for (i = 0; i < num_cols; i++)
        printf("%d ", starting_pos[i]);

    /* Preserve starting positions for display */
    for (i = 0; i < num_cols; i++)
        next_pos[i] = starting_pos[i];

    /* Place each term directly in its correct position */
    for (i = 1; i <= num_terms; i++) {
        j = next_pos[a[i].col]++;

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
    }
}

int main()
{
    term a[MAX], b[MAX];
    int matrix[MAX][MAX];
    int rows, cols, i, j, k = 1;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0 ||
        rows >= MAX || cols >= MAX) {
        printf("Invalid matrix dimensions.\n");
        return 1;
    }

    printf("Enter matrix elements row by row:\n");

    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            scanf("%d", &matrix[i][j]);

    /* Create triples representation */
    a[0].row = rows;
    a[0].col = cols;
    a[0].value = 0;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                a[k].row = i;
                a[k].col = j;
                a[k].value = matrix[i][j];
                k++;
            }
        }
    }

    a[0].value = k - 1;

    printf("\nOriginal triples (row col value):\n");
    for (i = 0; i < k; i++)
        printf("%d %d %d\n",
               a[i].row, a[i].col, a[i].value);

    fast_transpose(a, b);

    printf("\nTransposed triples (row col value):\n");
    for (i = 0; i < k; i++)
        printf("%d %d %d\n",
               b[i].row, b[i].col, b[i].value);

    printf("\nTransposed triples are in row-major order.\n");

    return 0;
}

