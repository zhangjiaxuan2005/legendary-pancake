//
// Created by 17246 on 2025/8/5.
//

#include <iostream>
using namespace std;

template <typename T>
auto add(T a, T b) -> decltype(a + b)
{
    return a + b;
}

auto lambda = [](int a, int b) -> int
{
    return a + b;
};

int main()
{
    auto a = add(1, 2);
    cout << a << endl;
    auto b = lambda(1, 2);
    cout << b << endl;
    return 0;
}
