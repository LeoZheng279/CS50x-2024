// Problem Set 2 - Scrabble
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int upper(string str, int length);
int calc(string str, int length);

int main()
{
    int score_a, score_b;

    string a = get_string("Player1: ");
    string b = get_string("Player2: ");

    int l_a = strlen(a);
    int l_b = strlen(b);
    upper(a, l_a);
    upper(b, l_b);

    score_a = calc(a, l_a);
    score_b = calc(b, l_b);

    if (score_a > score_b)
        printf("Player 1 wins!");
    else if (score_b > score_a)
        printf("Player 2 wins!");
    else
        printf("Tie!");
}

int upper(string str, int length)
{
    for (int i = 0; i < length; i++)
    {
        str[i] = toupper(str[i]);
    }
    return 0;
}

int calc(string str, int length)
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        if (str[i] == 'D' || str[i] == 'G')
            sum += 2;
        else if (str[i] == 'B' || str[i] == 'C' || str[i] == 'M' || str[i] == 'P')
            sum += 3;
        else if (str[i] == 'F' || str[i] == 'H' || str[i] == 'V' || str[i] == 'W' || str[i] == 'Y')
            sum += 4;
        else if (str[i] == 'K')
            sum += 5;
        else if (str[i] == 'J' || str[i] == 'X')
            sum += 8;
        else if (str[i] == 'Q' || str[i] == 'Z')
            sum += 10;
        else if (str[i] >= 'A' && str[i] <= 'Z')
            sum += 1;
    }
    return sum;
}
