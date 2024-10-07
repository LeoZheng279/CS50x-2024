// Problem Set 1 - Mario (more)
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 0;
    int i, j;

    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    for (i = 1; i <= n; i++) // print n line(s)
    {
        for (j = 0; j < n - i; j++) // print space
            printf(" ");

        for (j = 1; j <= i; j++) // print #
            printf("#");

        printf("  ");

        for (j = 1; j <= i; j++) // print #
            printf("#");

        printf("\n");
    }
}
