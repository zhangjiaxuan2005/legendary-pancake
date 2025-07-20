//
// Created by 17246 on 2025/7/16.
//
#include <stdio.h>
#include <stdlib.h>

void method(int *p,int size)
{
    for (int i = 0; i <= size; i++)
    {
        scanf("%d",p+i);
    }
}
int main()
{
    int* p = (int*)malloc(5 * sizeof(int));
    int size = 5;
    if (p == NULL)
    {
        printf("malloc error");
        return 0;
    }
    method(p,size);
    for (int i = 0; i <= size; i++)
    {
        printf("%d",p[i]);
    }
    free(p);
    return 0;
}
