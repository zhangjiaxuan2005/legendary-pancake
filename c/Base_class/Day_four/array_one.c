//
// Created by 17246 on 2025/7/16.
//
#include <stdio.h>

int main()
{
    int arr[5] = {33, 2, 22, 44, 55};
    int max_index = 0;
    for (int i = 0; i < 5; ++i)
    {
        if (arr[i] > arr[max_index])
        {
            max_index = i;
        }
    }
    printf("max_number = %d\n", arr[max_index]);
}
