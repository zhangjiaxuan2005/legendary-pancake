//
// Created by 17246 on 2025/7/16.
//
#include <stdio.h>

int binary_search(const int* arr, int len, int num)
{
    int left = 0;
    int right = len - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (arr[mid] == num)
        {
            return mid;
        }
        else if (arr[mid] > num)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}


int insert_search(const int* arr, int len, int num)
{
    int left = 0;
    int right = len - 1;
    while (left <= right)
    {
        int mid = left + (right - left) * (num - arr[left]) / (arr[right] - arr[left]);
        if (arr[mid] == num)
        {
            return mid;
        }
        else if (arr[mid] > num)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}

int main()
{
    int arr[] = {7, 23, 79, 81, 103, 127, 131, 147};
    int len = sizeof(arr) / sizeof(arr[0]);
    int num;
    printf("请输入要查找的数字:");
    scanf("%d", &num);
    int index = binary_search(arr, len, num);
    if (index == -1)
    {
        printf("查找失败");
    }
    else
    {
        printf("查找成功,下标为:%d", index);
    }
    return 0;
}

