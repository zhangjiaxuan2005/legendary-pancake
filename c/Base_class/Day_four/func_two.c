//
// Created by 17246 on 2025/7/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int number = rand() % 100 + 1;
    int guess;
    while (1)
    {
        scanf("%d", &guess);
        if (guess > number)
        {
            printf("Too high!\n");
        }
        else if (guess < number)
        {
            printf("Too low!\n");
        }
        else
        {
            printf("Congratulations! You guessed the number.\n");
            break;
        }
    }
}
