//
// Created by 17246 on 2025/7/16.
//
#include<stdio.h>

void* print()
{
    printf("hello world!\n");
    return 0;
}

int add(int a,int b)
{
    return a+b;
}


int main()
{
    void (*p1)()=print;
    p1();
    int (*p2)(int,int)=add;
    printf("%d",p2(1,2));

}
