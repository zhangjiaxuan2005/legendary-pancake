//
// Created by 17246 on 2025/8/4.
//
#include <algorithm>
#include <memory>
#include <iostream>
#include <random>

using namespace std;

int main()
{
    int* arr = unique_ptr<int []>(new int[10]).get();
    for (int i = 0; i < 10; i++)
    {
        arr[i] = i;
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(arr, arr + 10, gen);

    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10 - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j],arr[j+1]);
                // int temp = arr[j];
                // arr[j] = arr[j + 1];
                // arr[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
