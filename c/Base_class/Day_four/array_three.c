//
// Created by 17246 on 2025/7/16.
//
#include <stdio.h>
int swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
    return 0;
}

int bub_sort(int* arr, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    return 0;
}

int select_sort(int* arr, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            swap(arr[i], arr[min_index]);
        }
    }
    return 0;
}


int main()
{
    int arr[] = {7, 23, 79, 81, 103, 127, 131, 147};
    int len = sizeof(arr) / sizeof(arr[0]);
    bub_sort(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}

