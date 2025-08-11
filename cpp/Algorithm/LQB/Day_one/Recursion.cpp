//
// Created by 17246 on 2025/8/2
// QJ.760
//

#include <iostream>
using namespace std;
int count = 0;

void dfs(int n)
{
    if (n == 0)
    {
        return;
    }
    for (int i = 0; i <= n / 2; i++)
    {
        dfs(i);
    }
    count++;
}

int main()
{
    int n;
    cin >> n;
    dfs(n);
    cout << count;
}
