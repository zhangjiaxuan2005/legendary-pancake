//
// Created by 17246 on 2025/8/2.
//
#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<int, int> m = {{1, 2}, {3, 4}};
    for (const auto element : m)
    {
        cout << element.first << endl;
        cout << element.second << endl;
    }
}
