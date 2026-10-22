
#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];
} polynomial;

polynomial add(polynomial a, polynomial b)
{
    polynomial c;
    int i, exp;

    c.degree = (a.degree > b.degree) ? a.degree : b.degree;

    for (i = 0; i <= c.degree; i++)
        c.coef[i] = 0;

    for (exp = 0; exp <= a.degree; exp++)
        c.coef[c.degree - exp] += a.coef[a.degree - exp];

    for (exp = 0; exp <= b.degree; exp++)
        c.coef[c.degree - exp] += b.coef[b.degree - exp];

    return c;
}

void display(polynomial p)
{
    int i, exp, printed = 0;
    float value;

    for (i = 0; i <= p.degree; i++) {
        value = p.coef[i];
        exp = p.degree - i;

        if (value == 0)
            continue;

        if (printed && value > 0)
            printf(" + ");
        else if (printed && value < 0)
            printf(" - ");
        else if (value < 0)
            printf("-");

        if (printed)
            value = (value < 0) ? -value : value;
        else if (value < 0)
            value = -value;

        if (exp == 0)
            printf("%g", value);
        else if (exp == 1) {
            if (value == 1)
                printf("x");
            else
                printf("%gx", value);
        }
        else {
            if (value == 1)
                printf("x^%d", exp);
            else
                printf("%gx^%d", value, exp);
        }

        printed = 1;
    }

    if (!printed)
        printf("0");

    printf("\n");
}

int main()
{
    polynomial a, b, c;
    int i;

    printf("Enter degree of first polynomial: ");
    scanf("%d", &a.degree);

    printf("Enter coefficients from highest power to constant:\n");
    for (i = 0; i <= a.degree; i++)
        scanf("%f", &a.coef[i]);

    printf("Enter degree of second polynomial: ");
    scanf("%d", &b.degree);

    printf("Enter coefficients from highest power to constant:\n");
    for (i = 0; i <= b.degree; i++)
        scanf("%f", &b.coef[i]);

    c = add(a, b);

    printf("First polynomial: ");
    display(a);

    printf("Second polynomial: ");
    display(b);

    printf("Sum: ");
    display(c);

    return 0;
}

