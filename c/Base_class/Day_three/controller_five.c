//
// Created by 17246 on 2025/7/16.
//

#include <stdio.h>

int main()
{
    int x;
    int i = 0;
    scanf("%d", &x);
    while (i * i <= x)
    {
        i++;
    }
    printf("%d\n", i - 1);
}
