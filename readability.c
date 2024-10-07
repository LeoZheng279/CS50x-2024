// Problem Set 2 - Readability
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    string para = get_string("Text: ");
    int total = strlen(para);
    for (int j = 0; j < total; j++)
        para[j] = tolower(para[j]);
    int letter = 0, word = 1, sentence = 0;
    float index;
    int index_;

    for (int i = 0; i < total; i++)
    {
        if (para[i] >= 'a' && para[i] <= 'z')
            letter += 1;
        else if (para[i] == ' ')
            word += 1;
        else if (para[i] == '.' || para[i] == '?' || para[i] == '!')
            sentence += 1;
    }

    index = 0.0588 * ((float) letter / (float) word * 100) -
            0.296 * ((float) sentence / (float) word * 100) - 15.8;

    // 实现四舍五入的一个很好的方法：(int) (float +0.5)

    index_ = (int) (index + 0.5);
    if (index >= 1 && index <= 16)
        printf("Grade %i\n", index_);
    else if (index >= 16)
        printf("Grade 16+\n");
    else
        printf("Before Grade 1\n");
}
