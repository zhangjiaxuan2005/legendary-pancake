
//
// Created by 17246 on 2025/8/1.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void printVector(int i)
{
    cout << i << " ";
}

int main()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.insert(v.begin(), 10);
    auto it = v.begin();
    while (it != v.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
    for (const auto v1 : v)
    {
        cout << v1 << " ";
    }
    cout << endl;
    ranges::for_each(v, printVector);
    ranges::for_each(v, [](int& i) { i *= 2; });
    cout << endl;
    for (const auto v1 : v)
    {
        cout << v1 << " ";
    }
    auto it1 = ranges::find(v, 1);
    if (it1 != v.end())
    {
        cout << "找到" << endl;
    }
}
