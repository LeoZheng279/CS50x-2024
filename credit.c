// Problem Set 1 - Credit
#include <cs50.h>
#include <stdio.h>

string check1(long int num, int num_);
int check2(long int num, int length);

int main(void) // Main program
{
    long int num, num_;
    int length = 0;
    string card;
    num = get_long("Number：");
    num_ = num;

    do
    {
        num_ = num_ / 10;
        length++;
    }
    while (num_ > 100);

    length = length + 2;
    card = check1(num_, length);

    if (check2(num, length))
        card = "INVALID";

    printf("%s\n", card);
}

string check1(long int num_, int length) // preliminary check
{
    if ((num_ == 34 || num_ == 37) && length == 15)
        return "AMEX";
    else if ((51 <= num_ && num_ <= 55) && length == 16)
        return "MASTERCARD";
    else if ((num_ / 10 == 4) && (length == 16 || length == 13))
        return "VISA";
    else
        return "INVALID";
}

int check2(long int num, int length) // further check using the Luhn’s Algorithm
{

    int i, sum1 = 0, sum2 = 0, temp = 0;
    for (i = 1; i <= length; i++)
    {
        if (i % 2 != 0)
            sum1 += num % 10;
        else
        {
            temp = (num % 10) * 2;
            if (temp < 10)
                sum2 += temp;
            else
                sum2 += (temp / 10 + temp % 10);
        }

        num = num / 10;
    }

    // printf("%i\n", sum1);
    // printf("%i\n", sum2);

    if ((sum1 + sum2) % 10 == 0)
        return 0;
    else
        return 1;
}
