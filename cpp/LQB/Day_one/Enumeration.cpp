//
// Created by 17246 on 2025/8/2.
// QJ 191
//

#include <iostream>
using namespace std;

int check(int n)
{
    while (n)
    {
        int i = n % 10;
        if (i == 2 || i == 0 || i == 1 || i == 9)
        {
            return 1;
        }
        n /= 10;
    }
    return 0;
}


int main()
{
    int n, sum = 0;
    cin >> n;
    for (int i = 0; i <= n; i++)
    {
        if (check(i))
        {
            sum += i;
        }
    }
    cout << sum;
}
