//
// Created by 17246 on 2025/7/17.
//
#include <stdio.h>
int main()
{
    FILE* fp = fopen("test.txt","w");
    if (fp == NULL)
    {
        printf("fopen error");
        return 0;
    }
    fputc('a',fp);
    fputc('b',fp);
    fputc('c',fp);
    fputc('\n',fp);
    fputs("hello world",fp);
    fclose(fp);
    return 0;
}
