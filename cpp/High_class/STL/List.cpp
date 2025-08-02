//
// Created by 17246 on 2025/8/2.
//
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    list l = {4, 9, 1, 5, 2, 7, 3};
    l.sort();
    for (auto element : l)
    {
        cout << element << endl;
    }
}
