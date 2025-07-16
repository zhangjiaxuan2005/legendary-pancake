
//
// Created by 17246 on 2025/7/16.
//
#include<stdio.h>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int a, b;
    printf("请输入两个数字：");
    scanf("%d %d", &a, &b);
    printf("两个数字的和为：%d\n", add(a, b));
    return 0;
}
