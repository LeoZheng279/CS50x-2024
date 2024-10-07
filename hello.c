// Problem Set 1-Hello, it's me.
# include <stdio.h>
# include <cs50.h>

int main(void)
{
    string name = get_string("What's your name? ");
    printf("Hello, %s\n", name);

    return 0;
}
