//
// Created by 17246 on 2025/7/16.
//
#include <stdio.h>

int main()
{
    int arr[10]={1,2,3,4,5,6,7,8,9,10};

    for(int *p=arr;p<arr+10;p++)
    {
        printf("%d",*p);
    }
    return 0;
}
