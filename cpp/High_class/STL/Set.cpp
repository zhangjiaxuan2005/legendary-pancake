//
// Created by 17246 on 2025/8/2.
//
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    set s = {make_pair(1, 2), make_pair(3, 4)};
    for (const pair element : s)
    {
        cout << element.first << endl;
        cout << element.second << endl;
    }
}
