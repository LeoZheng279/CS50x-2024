#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // printf("%d", image[0][0].rgbtGreen);
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg =
                (int) ((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0 +
                       0.5);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2.0; j++)
        {
            temp1 = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = temp1;
            temp1 = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = temp1;
            temp1 = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = temp1;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int sum1 = 0, sum2 = 0, sum3 = 0, i1, j1, i, j;
    float counter = 0.0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            for (i1 = i - 1; i1 < i + 2; i1++)
            {
                for (j1 = j - 1; j1 < j + 2; j1++)
                {
                    if (i1 >= 0 && i1 <= (height - 1) && j1 >= 0 && j1 <= (width - 1))
                    {
                        sum1 += image[i1][j1].rgbtRed;
                        sum2 += image[i1][j1].rgbtGreen;
                        sum3 += image[i1][j1].rgbtBlue;
                        counter += 1.0;
                    }
                }
            }
            temp[i][j].rgbtRed = round(sum1 / counter);
            temp[i][j].rgbtGreen = round(sum2 / counter);
            temp[i][j].rgbtBlue = round(sum3 / counter);
            sum1 = 0;
            sum2 = 0;
            sum3 = 0;
            counter = 0.0;
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gxr = 0, Gyr = 0, Gxg = 0, Gyg = 0, Gxb = 0, Gyb = 0, i1, j1, i, j;
    int x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            for (i1 = i - 1; i1 < i + 2; i1++)
            {
                for (j1 = j - 1; j1 < j + 2; j1++)
                {
                    if (i1 >= 0 && i1 <= (height - 1) && j1 >= 0 && j1 <= (width - 1))
                    {
                        Gxr += image[i1][j1].rgbtRed * x[j1 - j + 1][i1 - i + 1];
                        Gxg += image[i1][j1].rgbtGreen * x[j1 - j + 1][i1 - i + 1];
                        Gxb += image[i1][j1].rgbtBlue * x[j1 - j + 1][i1 - i + 1];

                        Gyr += image[i1][j1].rgbtRed * y[j1 - j + 1][i1 - i + 1];
                        Gyg += image[i1][j1].rgbtGreen * y[j1 - j + 1][i1 - i + 1];
                        Gyb += image[i1][j1].rgbtBlue * y[j1 - j + 1][i1 - i + 1];
                    }
                }
            }

            temp[i][j].rgbtRed = round(sqrt(Gxr * Gxr + Gyr * Gyr)) <= 255
                                     ? round(sqrt(Gxr * Gxr + Gyr * Gyr))
                                     : 255;
            temp[i][j].rgbtGreen = round(sqrt(Gxg * Gxg + Gyg * Gyg)) <= 255
                                       ? round(sqrt(Gxg * Gxg + Gyg * Gyg))
                                       : 255;
            temp[i][j].rgbtBlue = round(sqrt(Gxb * Gxb + Gyb * Gyb)) <= 255
                                      ? round(sqrt(Gxb * Gxb + Gyb * Gyb))
                                      : 255;
            Gxr = 0;
            Gyr = 0;
            Gxg = 0;
            Gyg = 0;
            Gxb = 0;
            Gyb = 0;
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
