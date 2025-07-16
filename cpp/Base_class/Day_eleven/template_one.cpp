//
// Created by 17246 on 2025/7/15.
//

#include <iostream>
using namespace std;

template <typename T>
void my_swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void my_sort(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int min = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            my_swap(arr[min], arr[i]);
        }
    }
}

template <typename T>
void my_print(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int arr1[] = {4, 2, 5, 3, 6, 1};
    char arr2[] = "badcfe";

    my_sort(arr1, 6);
    my_sort(arr2, 6);

    my_print(arr1, 6);
    my_print(arr2, 6);
}
