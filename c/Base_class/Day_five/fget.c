//
// Created by 17246 on 2025/7/17.
//
#include <stdio.h>
int main()
{
    FILE* fp = fopen("test.txt","r");
    if (fp == NULL)
    {
        printf("fopen error");
        return 0;
    }
    while (!feof(fp))
    {
        int ch = fgetc(fp);
        printf("%c",ch);
    }
    fclose(fp);
    return 0;
}
